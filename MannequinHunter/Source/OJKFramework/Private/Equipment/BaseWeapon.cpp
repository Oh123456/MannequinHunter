// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseWeapon.h"
#include "OJKFramework.h"
#include "Components/ShapeComponent.h"
#include "Components/MeshComponent.h"
#include "BaseActionCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"

using FAttackObject = FWeaponHitData::FAttackObject;

// Sets default values
ABaseWeapon::ABaseWeapon() : AEquipment(EEquipmentType::E_Weapon),
weaponTraceHitParameter(),
cylinderComponent(nullptr), hitCheckBeginDelegate(), hitCheckDelegate(), hitCheckEndDelegate()
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
	if (weaponHitData.numberOfAttackPerObject == -1 && weaponHitData.numberOfAttackObject == -1)
		return false;

	TArray<TSharedPtr<FAttackObject>>& attackObjects = weaponHitData.attackObjects;

	TSharedPtr<FAttackObject>* findObject = attackObjects.FindByPredicate(
		[&damagedObject](const TSharedPtr<FAttackObject>& item)
		{
			return item->attackObject == damagedObject;
		});

	
	if (findObject == nullptr)
	{
		if (weaponHitData.numberOfAttackObject > 0 && attackObjects.Num() >= weaponHitData.numberOfAttackObject)
			return false;

		TSharedPtr<FAttackObject> attackObject = MakeShared<FAttackObject>(FAttackObject(damagedObject));
		attackObjects.Add(attackObject);
		findObject = &attackObject;
	}

	if (weaponHitData.numberOfAttackPerObject < 0 || (*findObject)->hitCount >= weaponHitData.numberOfAttackPerObject)
		return false;
#ifdef UE_BUILD_DEBUG
	UE_LOG(Framework, Warning, TEXT("hitCount %f "), ((*findObject)->hitCount));
#endif
	++((*findObject)->hitCount);

	return true;
	
}

void ABaseWeapon::ApplyDamage(UCombatComponent* damagedObject, const FHitResult& hitResult)
{
	UCharacterCombatComponent* ownerCharacterCombat = weaponData.ownerCharacter->GetCombatComponent();
	ownerCharacterCombat->ApplyDamage(damagedObject, Owner->GetInstigatorController(), this, UDamageType::StaticClass());
}

void ABaseWeapon::SetWeaponOwner(AActor* weaponOwner)
{
	weaponData.ownerCharacter = Cast<ABaseActionCharacter>(weaponOwner);
	ABaseActionCharacter* ownerCharacter = weaponData.ownerCharacter;
	SetOwner(ownerCharacter);

	if (ownerCharacter == nullptr)
		return;

	
	if (bUseCylinder)
	{
		if (!CheckCylinderComponent())
			cylinderComponent = FindComponentByClass<UShapeComponent>();

		if (!CheckCylinderComponent())
			return;
		
		hitCheckBeginDelegate.BindLambda(
			[this]()
			{
				this->SetCylinderActive(true);
			});
		SetCylinder();
		hitCheckEndDelegate.BindLambda(
			[this]()
			{
				this->ClearHitObjects();
				this->SetCylinderActive(false);
			});
		SetCylinderActive(false);
	}
	else
	{
		weaponTraceHitParameter.ignoreActor.Add(Owner);
		hitCheckBeginDelegate.BindLambda(
			[this]()
			{
				this->ClearHitObjects();
				this->weaponHitData.startLocation = this->weaponMeshComponent->GetSocketLocation(this->weaponTraceHitParameter.startName);
				this->weaponHitData.endLocation = this->weaponMeshComponent->GetSocketLocation(this->weaponTraceHitParameter.endName);
			});
		
		SetTraceHit();
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
	bool isHit = UKismetSystemLibrary::SphereTraceMulti(this, weaponHitData.startLocation, weaponHitData.endLocation
														, weaponTraceHitParameter.radius, weaponHitData.attackAbleTraceType
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
	
	//SetWeaponOwner(GetOwner());
}

void ABaseWeapon::SetCylinder()
{
	cylinderComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::HitCheckCylinder);
}

void ABaseWeapon::SetTraceHit()
{
	hitCheckDelegate.BindUObject(this, &ABaseWeapon::HitCheckTrace);
}

bool ABaseWeapon::CheckCylinderComponent()
{
	return cylinderComponent != nullptr;
}

