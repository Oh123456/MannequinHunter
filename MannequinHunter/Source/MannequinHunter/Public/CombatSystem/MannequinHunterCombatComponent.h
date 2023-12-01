// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/PlayerCharacterCombatComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "MannequinHunterCombatComponent.generated.h"

/**
 * 
 */



UCLASS()
class MANNEQUINHUNTER_API UMannequinHunterCombatComponent : public UPlayerCharacterCombatComponent
{
	GENERATED_BODY()
	

public:
	void SetPlyerInputType(EPlayerInputType type) { playerInputType = type; }
	EPlayerInputType GetPlayerInputType() const { return playerInputType; }

private:
	EPlayerInputType playerInputType;
};
