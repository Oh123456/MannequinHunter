// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/BaseCombatAnimationData.h"
#include "Equipment/FistWeapon.h"
#include "FistCombatAnimationData.generated.h"

class UAnimMontage;
enum class ECharacterCombatMontageType : uint8;


USTRUCT()
struct MANNEQUINHUNTER_API FFistAnimMontageHitBoxFlag 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Bitmask, BitmaskEnum = "EFistWeaponSlotFlag"))
	uint8 flag;
};

USTRUCT()
struct MANNEQUINHUNTER_API FFistAnimMontageHitBoxFlagArray 
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly)
	TArray<FFistAnimMontageHitBoxFlag> flags;
};

USTRUCT()
struct MANNEQUINHUNTER_API FFistAnimMontageArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> montages;

	UPROPERTY(EditDefaultsOnly)
	TArray<FFistAnimMontageHitBoxFlagArray> montageFlag;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MANNEQUINHUNTER_API UFistCombatAnimationData : public UBaseCombatAnimationData
{
	GENERATED_BODY()
	
public:
	const TArray<FFistAnimMontageHitBoxFlagArray>* GetHitBoxSlotFlag(const ECharacterCombatMontageType type);

public:
	virtual const TArray<UAnimMontage*>* GetMontageArray(const ECharacterCombatMontageType type) const override;

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterCombatMontageType, FFistAnimMontageArray> combatMontageMap = {};
};
