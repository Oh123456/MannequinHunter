// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/CombatComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "CombatSystem/DeathInfo.h"
#include "OJKFramework.h"
#include "DebugLog.h"
#include "DamageType/ActionGameDamageTypeInterface.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent() : 
	deathEvent(), isImmortality(false) , status()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	
}

UCombatComponent::~UCombatComponent()
{

}

bool UCombatComponent::ApplyDamage(UCombatComponent* damageComponent, AController* eventInstigator, AActor* damageCauser,TSubclassOf<UDamageType> damageTypeClass)
{
	if (damageComponent == nullptr)
		return false;
	
	if (damageComponent->GetImmortality() || damageComponent->IsDeath())
	{
		UE_LOG(Framework,Log,TEXT("Avoidance !! "))
		return false;
	}

	float actualDamage = CalculateApplyDamage();
	if ((actualDamage != 0.f))
	{
		// make sure we have a good damage type
		TSubclassOf<UDamageType> const ValidDamageTypeClass = damageTypeClass ? damageTypeClass : TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent damageEvent(ValidDamageTypeClass);

		damageComponent->TakeDamage(actualDamage, damageEvent, eventInstigator, damageCauser);
	}
	return true;
}


void UCombatComponent::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	damageCauserActor = damageCauser;
	const TSharedPtr<const FStatusData>& statusData = status.GetStatusData();
	if (statusData == nullptr)
	{
		UE_LOG_WARNING(Framework, TEXT("%s StatusData is None"), *UKismetSystemLibrary::GetDisplayName(GetOwner()));
		return;
	}
	int32 actualDamage = CalculateTakeDamage(damageAmount);

	if (damageEvent.DamageTypeClass->ImplementsInterface(UActionGameDamageTypeInterface::StaticClass()))
	{
		IActionGameDamageTypeInterface* damageType = Cast<IActionGameDamageTypeInterface>(damageEvent.DamageTypeClass->GetDefaultObject());
		actualDamage = damageType->ExecuteDamageType(actualDamage, this, eventInstigator, damageCauser);
	}

	if (!isImmortality)
	{
		status.AddHP(-actualDamage);

		takeDamage.Broadcast(status, actualDamage, damageEvent, eventInstigator, damageCauser);

		if (statusData->health <= 0)
		{
			FDeathInfo deathInfo = FDeathInfo();
			deathEvent.Broadcast(deathInfo);
		}
	}
}


bool UCombatComponent::IsDeath() const
{
	const TSharedPtr<FStatusData>& data = status.GetStatusData();
	if (data == nullptr)
		return true;

	return data->health <= 0;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	//status.SetStatus(statusDataAsset);
	//status.health = status.maxHealth;
}

float UCombatComponent::CalculateApplyDamage()
{
	if (status.GetStatusData() == nullptr)
		return 1.0f;
	return status.GetStatusData()->attack;
}

int32 UCombatComponent::CalculateTakeDamage(float damageAmount)
{
	const TSharedPtr<const FStatusData>& statusData = status.GetStatusData();
	if (statusData)
		return static_cast<int32>(damageAmount) - statusData->defensive;

	return static_cast<int32>(damageAmount);
}

