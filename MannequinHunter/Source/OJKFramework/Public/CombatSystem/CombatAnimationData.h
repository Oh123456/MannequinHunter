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
	None = 0,

	Attack1 = 10				UMETA(DisplayName = "Attack1"),
	Attack2						UMETA(DisplayName = "Attack2"),
	Attack3						UMETA(DisplayName = "Attack3"),
	Attack4						UMETA(DisplayName = "Attack4"),
	Attack5						UMETA(DisplayName = "Attack5"),
	Attack6						UMETA(DisplayName = "Attack6"),
	Attack7						UMETA(DisplayName = "Attack7"),
	Attack8						UMETA(DisplayName = "Attack8"),
	Attack9						UMETA(DisplayName = "Attack9"),
	Attack10					UMETA(DisplayName = "Attack10"),
	Attack11					UMETA(DisplayName = "Attack11"),
	Attack12					UMETA(DisplayName = "Attack12"),
	Attack13					UMETA(DisplayName = "Attack13"),
	Attack14					UMETA(DisplayName = "Attack14"),
	Attack15					UMETA(DisplayName = "Attack15"),
	Attack16					UMETA(DisplayName = "Attack16"),
	Attack17					UMETA(DisplayName = "Attack17"),
	Attack18					UMETA(DisplayName = "Attack18"),
	Attack19					UMETA(DisplayName = "Attack19"),
	Attack20					UMETA(DisplayName = "Attack20"),


	Dodge1						UMETA(DisplayName = "Dodge1"),
	Dodge2						UMETA(DisplayName = "Dodge2"),
	Dodge3						UMETA(DisplayName = "Dodge3"),
	Dodge4						UMETA(DisplayName = "Dodge4"),
	Dodge5						UMETA(DisplayName = "Dodge5"),

	Turn1 = 250					UMETA(DisplayName = "Turn1"),
	Turn2						UMETA(DisplayName = "Turn2"),
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
