// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseCombatAnimationData.generated.h"

enum class ECharacterCombatMontageType : uint8;
/**
 * 
 */

USTRUCT()
struct FAnimSlotData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	bool isSuperArmor = false;

	UPROPERTY(EditDefaultsOnly)
	bool isImmortality = false;
};


UCLASS(abstract, BlueprintType, Blueprintable)
class OJKFRAMEWORK_API UBaseCombatAnimationData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual const TArray<UAnimMontage*>* GetMontageArray(const ECharacterCombatMontageType type) const PURE_VIRTUAL(UBaseCombatAnimationData::GetMontageArray, return nullptr;);
	virtual const UAnimMontage* GetMontage(const ECharacterCombatMontageType type, const int32 index) const;
};
