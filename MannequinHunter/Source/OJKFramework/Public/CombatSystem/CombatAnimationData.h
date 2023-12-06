// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatComponent.h"
#include "CombatAnimationData.generated.h"

/**
 * 
 */

class UAnimMontage;
class UDataTable;
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
enum class ECharacterCombatMontageType : uint8
{
	None = 0,

	Attack1 = 10				,				
	Attack2						,
	Attack3						,
	Attack4						,
	Attack5						,
	Attack6						,
	Attack7						,
	Attack8						,
	Attack9						,
	Attack10					,
	Attack11					,
	Attack12					,
	Attack13					,
	Attack14					,
	Attack15					,
	Attack16					,
	Attack17					,
	Attack18					,
	Attack19					,
	Attack20					,
	Attack21					,
	Attack22					,
	Attack23					,
	Attack24					,
	Attack25					,
	Attack26					,
	Attack27					,
	Attack28					,
	Attack29					,
	Attack30					,
	Attack31					,
	Attack32					,
	Attack33					,
	Attack34					,
	Attack35					,
	Attack36					,
	Attack37					,
	Attack38					,
	Attack39					,
	Attack40					,
	Attack41					,
	Attack42					,
	Attack43					,
	Attack44					,
	Attack45					,
	Attack46					,
	Attack47					,
	Attack48					,
	Attack49					,
	Attack50					,


	Dodge1 = 100				,
	Dodge2						,
	Dodge3						,
	Dodge4						,
	Dodge5						,

	Turn1 = 250					,
	Turn2						,
};


UCLASS(BlueprintType,Blueprintable)
class OJKFRAMEWORK_API UCombatAnimationData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UCombatAnimationData();
	virtual ~UCombatAnimationData();

	const FAnimMontageArray* GetMontageArray(const ECharacterCombatMontageType type) const;
	const UAnimMontage* GetMontage(const ECharacterCombatMontageType type, const int32 index) const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("AssetItems", GetFName()); }

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterCombatMontageType, FAnimMontageArray> combatMontageMap;
};
