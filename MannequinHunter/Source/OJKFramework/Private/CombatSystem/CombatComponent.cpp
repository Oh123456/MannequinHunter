// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/CombatComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "CombatSystem/DeathInfo.h"
#include "OJKFramework.h"
#include "DebugLog.h"

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

void UCombatComponent::ApplyDamage(UCombatComponent* damageComponent, AController* eventInstigator, AActor* damageCauser,TSubclassOf<UDamageType> damageTypeClass)
{
	if (damageComponent == nullptr)
		return;
	
	float actualDamage = CalculateApplyDamage();
	if ((actualDamage != 0.f))
	{
		// make sure we have a good damage type
		TSubclassOf<UDamageType> const ValidDamageTypeClass = damageTypeClass ? damageTypeClass : TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent damageEvent(ValidDamageTypeClass);

		damageComponent->TakeDamage(actualDamage, damageEvent, eventInstigator, damageCauser);
	}

}

void UCombatComponent::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	damageCauserActor = damageCauser;
	TSharedPtr<FStatusData>& statusData = status.GetStatusData();
	if (statusData == nullptr)
	{
		UE_LOG_WARNING(Framework, TEXT("%s StatusData is None"), *UKismetSystemLibrary::GetDisplayName(GetOwner()));
		return;
	}
	int32 actualDamage = CalculateTakeDamage(damageAmount);
	statusData->health -= actualDamage;
	
	takeDamage.Broadcast(status, actualDamage, damageEvent, eventInstigator, damageCauser);

	if (!isImmortality && statusData->health <= 0)
	{
		FDeathInfo deathInfo = FDeathInfo();
		deathEvent.Broadcast(deathInfo);
	}
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
	TSharedPtr<FStatusData>& statusData = status.GetStatusData();
	if (statusData)
		return static_cast<int32>(damageAmount) - statusData->defensive;

	return static_cast<int32>(damageAmount);
}

