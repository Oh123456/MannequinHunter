// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/PlayerCharacterCombatComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "Engine/DataTable.h"
#include "CombatSystem/CombatComponent.h"
#include "MannequinHunterCombatComponent.generated.h"


UENUM(BlueprintType)
enum class ERYUWeaponType : uint8
{
	None = 0,
	Katana = 1,
	Fist,

};

/**
 * 
 */
USTRUCT(Blueprinttype)
struct FCommandDataTable : public FTableRowBase
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<EPlayerInputType> attackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	ECharacterCombatontageType useAnimSlot;
};


UCLASS()
class MANNEQUINHUNTER_API UMannequinHunterCombatComponent : public UPlayerCharacterCombatComponent
{
	GENERATED_BODY()
	

public:
	void SetPlyerInputType(EPlayerInputType type) { playerInputType = type; }
	EPlayerInputType GetPlayerInputType() const { return playerInputType; }

	void SetCombatAnimationData(ERYUWeaponType type) { combatAnimationData = weaponTypeAnimationData[type]; }

	void AddInputList(EPlayerInputType type);
	void ClearInputList();
	TList<EPlayerInputType>* GetInputListHead() const { return inputListHead; }

private:
	void UnLinkInputList(TList<EPlayerInputType>* list);

private:
	EPlayerInputType playerInputType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TMap<ERYUWeaponType, TObjectPtr<class UCombatAnimationData>> weaponTypeAnimationData;
private:
	//TODO:: 난중에 커스텀 리스트 만들것..
	TList<EPlayerInputType>* inputListHead;

};
