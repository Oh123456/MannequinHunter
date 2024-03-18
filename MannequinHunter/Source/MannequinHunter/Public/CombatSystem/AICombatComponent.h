// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "AICombatComponent.generated.h"

/**
 * 
 */

class ABaseEnemyCharacter;

UCLASS()
class MANNEQUINHUNTER_API UAICombatComponent : public UCharacterCombatComponent
{
	GENERATED_BODY()
	
protected:
	ABaseEnemyCharacter* GetEnemyOwner();
protected:
	virtual void OnHitEnd() override;
	virtual void BeginPlay() override;
protected:
	virtual void TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser) override;

};
