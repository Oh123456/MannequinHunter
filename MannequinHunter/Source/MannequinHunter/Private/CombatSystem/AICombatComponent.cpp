// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/AICombatComponent.h"
#include "Character/BaseEnemyCharacter.h"
#include "Utility/MannequinHunterUtility.h"

ABaseEnemyCharacter* UAICombatComponent::GetEnemyOwner()
{
	return Cast<ABaseEnemyCharacter>(GetOwner());
}

void UAICombatComponent::OnHitEnd()
{
	Super::OnHitEnd();
	ABaseEnemyCharacter* enemy = GetEnemyOwner();
	if (enemy)
		enemy->SetState(EEnemyState::Idle);
}

void UAICombatComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAICombatComponent::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);
	ABaseEnemyCharacter* enemy = GetEnemyOwner();
	if (enemy)
		enemy->SetState(EEnemyState::Hit);
}

float UAICombatComponent::GetPlayRate(UAnimInstance* animInstance)
{
	return FMannequinHunterUtility::GetPlayRate(GetStatusData().GetStatusData()->attackSpeed);
}
