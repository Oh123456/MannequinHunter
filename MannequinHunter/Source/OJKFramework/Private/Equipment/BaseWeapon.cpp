// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseWeapon.h"
#include "OJKFramework.h"
#include "Components/ShapeComponent.h"
#include "Components/MeshComponent.h"
#include "BaseActionCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"

// Sets default values
ABaseWeapon::ABaseWeapon() : AEquipment(EEquipmentType::E_Weapon),
bUseCylinder(true), weaponTraceHitParameter(),
cylinderComponent(nullptr), hitCheckBeginDelegate(), hitCheckDelegate(), hitCheckEndDelegate(),
numberOfAttackObject(-1), numberOfAttackPerObject(1), attackObjects(),attackAbleTraceType(ETraceTypeQuery::TraceTypeQuery1)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseWeapon::SetCylinderActive(bool isActive)
{

	if (cylinderComponent == nullptr)
		return;
	if (isActive)
		cylinderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
		cylinderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


bool ABaseWeapon::CheckHitAble(UCombatComponent* damagedObject)
{
	if (numberOfAttackPerObject == -1 && numberOfAttackObject == -1)
		return false;

	TSharedPtr<FAttackObject>* findObject = attackObjects.FindByPredicate(
		[&damagedObject](const TSharedPtr<FAttackObject>& item)
		{
			return item->attackObject == damagedObject;
		});

	
	if (findObject == nullptr)
	{
		if (numberOfAttackObject > 0 && attackObjects.Num() >= numberOfAttackObject)
			return false;

		TSharedPtr<FAttackObject> attackObject = MakeShared<FAttackObject>(FAttackObject(damagedObject));
		attackObjects.Add(attackObject);
		findObject = &attackObject;
	}

	if (numberOfAttackPerObject < 0 || (*findObject)->hitCount >= numberOfAttackPerObject)
		return false;
#ifdef UE_BUILD_DEBUG
	UE_LOG(Framework, Warning, TEXT("hitCount %f "), ((*findObject)->hitCount));
#endif
	++((*findObject)->hitCount);

	return true;
	
}

void ABaseWeapon::ApplyDamage(UCombatComponent* damagedObject, const FHitResult& hitResult)
{
	UCharacterCombatComponent* ownerCharacterCombat = ownerCharacter->GetCombatComponent();
	ownerCharacterCombat->ApplyDamage(damagedObject, Owner->GetInstigatorController(), this, UDamageType::StaticClass());
}

void ABaseWeapon::SetWeaponOwner(AActor* weaponOwner)
{
	ownerCharacter = Cast<ABaseActionCharacter>(weaponOwner);
	SetOwner(ownerCharacter);

	if (ownerCharacter == nullptr)
		return;

	if (bUseCylinder)
	{
		cylinderComponent = FindComponentByClass<UShapeComponent>();
		if (cylinderComponent == nullptr)
		{

			return;
		}
		hitCheckBeginDelegate.BindLambda(
			[this]()
			{
				this->SetCylinderActive(true);
			});
		cylinderComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::HitCheckCylinder);
		hitCheckEndDelegate.BindLambda(
			[this]()
			{
				this->ClearHitObjects();
				this->SetCylinderActive(false);
			});
		cylinderComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		weaponTraceHitParameter.ignoreActor.Add(Owner);
		hitCheckBeginDelegate.BindLambda(
			[this]()
			{
				this->ClearHitObjects();
				this->startLocation = this->weaponMeshComponent->GetSocketLocation(this->weaponTraceHitParameter.startName);
				this->endLocation = this->weaponMeshComponent->GetSocketLocation(this->weaponTraceHitParameter.endName);
			});
		hitCheckDelegate.BindUObject(this, &ABaseWeapon::HitCheckTrace);

		hitCheckEndDelegate.BindUObject(this, &ABaseWeapon::ClearHitObjects);
	}
}

void ABaseWeapon::HitCheckCylinder(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor && otherActor != GetOwner() && (otherActor != this) && otherComp)
	{
		UCombatComponent* otherCombatComponent = otherActor->GetComponentByClass<UCombatComponent>();
		if (otherCombatComponent && CheckHitAble(otherCombatComponent))
		{
#ifdef UE_BUILD_DEBUG
			UE_LOG(Framework, Warning, TEXT("ApplyDamage %s "), *UKismetSystemLibrary::GetDisplayName(otherActor));
#endif
			ApplyDamage(otherCombatComponent, sweepResult);
		}
	}
}

void ABaseWeapon::HitCheckTrace()
{
	TArray<FHitResult> hits;
	bool isHit = UKismetSystemLibrary::SphereTraceMulti(this, startLocation,endLocation
														, weaponTraceHitParameter.radius, attackAbleTraceType
														,false, weaponTraceHitParameter.ignoreActor,EDrawDebugTrace::Type::ForOneFrame,
														OUT hits, true);

	if (isHit)
	{
		for (const FHitResult& hit : hits)
		{
			AActor* hitActor = hit.GetActor();
			UCombatComponent* combatComponent = hitActor->GetComponentByClass<UCombatComponent>();
			if (combatComponent && CheckHitAble(combatComponent))
				ApplyDamage(combatComponent, hit);
		}
	}
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SetWeaponOwner(GetOwner());
}

