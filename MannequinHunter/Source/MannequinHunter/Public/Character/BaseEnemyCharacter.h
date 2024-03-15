// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayerCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	None = 0,
	Idle = 1,
	Attack,
	Combat,
	Hit,
	AttackAble,
};



class UAICombatComponent;
UCLASS()
class MANNEQUINHUNTER_API ABaseEnemyCharacter : public ANonPlayerCharacter
{
	GENERATED_BODY()
	
public:
	ABaseEnemyCharacter();
};
