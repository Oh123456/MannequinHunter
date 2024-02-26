// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayerCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */

namespace EEnemyState
{
	enum Type
	{
		Idle,
		Move,
		Combat,
		Hit,
		END,
	};
}

class UAICombatComponent;
UCLASS()
class MANNEQUINHUNTER_API ABaseEnemyCharacter : public ANonPlayerCharacter
{
	GENERATED_BODY()
	
public:
	ABaseEnemyCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAICombatComponent> aiCombatComponent;
};
