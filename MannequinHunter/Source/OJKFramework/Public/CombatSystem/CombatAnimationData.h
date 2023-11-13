// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatAnimationData.generated.h"

/**
 * 
 */

class UAnimMontage;

USTRUCT()
struct OJKFRAMEWORK_API FAnimMontageArray
{
	GENERATED_BODY()

	const UAnimMontage* operator[](int idx)
	{
		return montages[idx];
	}
	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> montages;
};

UENUM(BlueprintType)
enum class ECharacterCombatontageType : uint8
{
	E_None = 0,

	E_Attack1 = 10	UMETA(DisplayName = "Attack1"),
	E_Attack2		UMETA(DisplayName = "Attack2"),
	E_Attack3		UMETA(DisplayName = "Attack3"),
	E_Attack4		UMETA(DisplayName = "Attack4"),
	E_Attack5		UMETA(DisplayName = "Attack5"),
	E_Attack6		UMETA(DisplayName = "Attack6"),
	E_Attack7		UMETA(DisplayName = "Attack7"),
	E_Attack8		UMETA(DisplayName = "Attack8"),
	E_Attack9		UMETA(DisplayName = "Attack9"),
	E_Attack10		UMETA(DisplayName = "Attack10"),


	E_Dodge1 = 20	UMETA(DisplayName = "Dodge1"),
	E_Dodge2		UMETA(DisplayName = "Dodge2"),
	E_Dodge3		UMETA(DisplayName = "Dodge3"),
	E_Dodge4		UMETA(DisplayName = "Dodge4"),
	E_Dodge5		UMETA(DisplayName = "Dodge5"),

	E_Turn1 = 250	UMETA(DisplayName = "Turn1"),
	E_Turn2			UMETA(DisplayName = "Turn2"),
};


UCLASS(BlueprintType,Blueprintable)
class OJKFRAMEWORK_API UCombatAnimationData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UCombatAnimationData();
	virtual ~UCombatAnimationData();

	const FAnimMontageArray* GetMontageArray(const ECharacterCombatontageType type) const;
	const UAnimMontage* GetMontage(const ECharacterCombatontageType type, const int32 index) const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("AssetItems", GetFName()); }
protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterCombatontageType, FAnimMontageArray> combatMontageMap;
	
};
