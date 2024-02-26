// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEnemyCharacter.h"
#include "Mannequin.generated.h"


namespace EEnemyState
{
	enum MannequinType
	{
		Test = END,
	};
}

UCLASS()
class MANNEQUINHUNTER_API AMannequin : public ABaseEnemyCharacter
{
	GENERATED_BODY()
	
};
