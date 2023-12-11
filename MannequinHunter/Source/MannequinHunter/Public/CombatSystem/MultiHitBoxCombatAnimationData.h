// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/BaseCombatAnimationData.h"
#include "CombatSystem/CombatAnimationEnums.h"
#include "MultiHitBoxCombatAnimationData.generated.h"


class UAnimMontage;

USTRUCT()
struct MANNEQUINHUNTER_API FMultiHitBoxAnimMontageArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> montages;

	UPROPERTY(EditDefaultsOnly)
	TArray<uint8> hitBoxSlots;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MANNEQUINHUNTER_API UMultiHitBoxCombatAnimationData : public UBaseCombatAnimationData
{
	GENERATED_BODY()
	
public:
	UMultiHitBoxCombatAnimationData();
	virtual ~UMultiHitBoxCombatAnimationData();

	const TArray<uint8>* GetHitBoxSlot(const ECharacterCombatMontageType type);

public:
	virtual const TArray<UAnimMontage*>* GetMontageArray(const ECharacterCombatMontageType type) const override;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("AssetItems", GetFName()); }

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterCombatMontageType, FMultiHitBoxAnimMontageArray> combatMontageMap = {};
};
