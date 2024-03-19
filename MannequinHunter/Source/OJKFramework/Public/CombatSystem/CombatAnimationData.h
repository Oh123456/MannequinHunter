// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCombatAnimationData.h"
#include "CombatComponent.h"
#include "CombatAnimationEnums.h"
#include "CombatAnimationData.generated.h"

/**
 * 
 */

class UAnimMontage;

USTRUCT()
struct OJKFRAMEWORK_API FAnimMontageArray : public FAnimSlotData
{
	GENERATED_BODY()

	const UAnimMontage* operator[](int idx)
	{
		return montages[idx];
	}
	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> montages;

};


UCLASS(BlueprintType,Blueprintable)
class OJKFRAMEWORK_API UCombatAnimationData : public UBaseCombatAnimationData
{
	GENERATED_BODY()

public:
	UCombatAnimationData();
	virtual ~UCombatAnimationData();


public:
	virtual const TArray<UAnimMontage*>* GetMontageArray(const ECharacterCombatMontageType type) const override;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("AssetItems", GetFName()); }
protected:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterCombatMontageType, FAnimMontageArray> combatMontageMap;
};
