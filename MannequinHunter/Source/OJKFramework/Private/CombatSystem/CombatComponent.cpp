// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/CombatComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "CombatSystem/DeathInfo.h"

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

void UCombatComponent::ApplyDamage(UCombatComponent* damageComponent, AController* eventInstigator, AActor* damageCauser, TSubclassOf<UDamageType> damageTypeClass)
{
	if (damageComponent == nullptr)
		return;
	
	float actualDamage = CalculateApplyDamage();
	if ((actualDamage != 0.f))
	{
		// make sure we have a good damage type
		TSubclassOf<UDamageType> const ValidDamageTypeClass = damageTypeClass ? damageTypeClass : TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent damageEvent(ValidDamageTypeClass);

		//damageComponent->GetOwner()->TakeDamage(actualDamage, DamageEvent, eventInstigator, damageCauser);
		damageComponent->TakeDamage(actualDamage, damageEvent, eventInstigator, damageCauser);
	}

}

void UCombatComponent::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	int32 actualDamage = CalculateTakeDamage(damageAmount);
	status.health -= actualDamage;

	takeDamage.Broadcast(status, actualDamage, damageEvent, eventInstigator, damageCauser);
	UE_LOG(LogTemp,Log,TEXT("tlqkf glxmek glxm"))

	if (!isImmortality && status.health <= 0)
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
	return status.attack;
}

int32 UCombatComponent::CalculateTakeDamage(float damageAmount)
{
	return static_cast<int32>(damageAmount) - status.defensive;
}

