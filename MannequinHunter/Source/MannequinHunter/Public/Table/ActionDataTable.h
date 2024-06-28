// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Character/PlayerCommonEnums.h"
#include "ActionDataTable.generated.h"

USTRUCT(Blueprinttype)
struct FActionTableData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float damageCoefficient = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	int32 useStamina = 10;

	UPROPERTY(EditDefaultsOnly)
	int32 recoveryStamina = 0;

	UPROPERTY(EditDefaultsOnly)
	bool isSuperArmor = false;

	UPROPERTY(EditDefaultsOnly)
	bool isImmortality = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDamageType> damageType = UDamageType::StaticClass();
};

USTRUCT(Blueprinttype)
struct FActionTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName actionName;

	UPROPERTY(EditDefaultsOnly)
	float damageCoefficient = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	int32 useStamina = 10;

	UPROPERTY(EditDefaultsOnly)
	int32 recoveryStamina = 0;

	UPROPERTY(EditDefaultsOnly)
	bool isSuperArmor = false;

	UPROPERTY(EditDefaultsOnly)
	bool isImmortality = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDamageType> damageType = UDamageType::StaticClass();

	UPROPERTY(EditDefaultsOnly)
	TMap<EWeaponType, FActionTableData> actionDataMap;
};


UCLASS()
class MANNEQUINHUNTER_API UActionDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
