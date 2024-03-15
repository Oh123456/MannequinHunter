// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseEnemyCharacter.h"
#include "CombatSystem/AICombatComponent.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	combatComponent = CreateDefaultSubobject<UAICombatComponent>(TEXT("AICombatSystem"));
}

