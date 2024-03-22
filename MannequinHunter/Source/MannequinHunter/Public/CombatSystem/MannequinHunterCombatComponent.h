// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/PlayerCharacterCombatComponent.h"
#include "Character/PlayerCommonEnums.h"
#include "Engine/DataTable.h"
#include "CombatSystem/Status.h"
#include "CombatSystem/CombatComponent.h"
#include "CommandListTree.h"
#include "MannequinHunterCombatComponent.generated.h"


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
	ECharacterCombatMontageType useAnimSlot;
};


struct FCommandListData
{
	using CommandListTree = TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>;
	using CommandListNode = TCommandListNode<EPlayerInputType, ECharacterCombatMontageType>;

	EPlayerInputType playerInputType;

	EWeaponType playerWeaponType;

	TSharedPtr<CommandListNode> currentCommandListNode = nullptr;
};

DECLARE_EVENT_OneParam(UMannequinHunterCombatComponent,FChangeWeaponType,EWeaponType);

UCLASS()
class MANNEQUINHUNTER_API UMannequinHunterCombatComponent : public UPlayerCharacterCombatComponent
{
	GENERATED_BODY()
	

	using CommandListTree = TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>;
	using CommandListNode = TCommandListNode<EPlayerInputType, ECharacterCombatMontageType>;

public:
	virtual ~UMannequinHunterCombatComponent();

	void SetPlyerInputType(EPlayerInputType type) { commandListData.playerInputType = type; }
	EPlayerInputType GetPlayerInputType() const { return commandListData.playerInputType; }

	void SetCombatAnimationData(EWeaponType type) { combatAnimationData = weaponTypeAnimationData[type]; }

	void SetWeaponType(EWeaponType type) { commandListData.playerWeaponType = type; OnChangeWeaponType.Broadcast(type); }
	EWeaponType GetWeaponType() const { return commandListData.playerWeaponType; }


	void ResetCommandList();
	const ECharacterCombatMontageType GetCommandMontageType();
	const ECharacterCombatMontageType GetCommandMontageType(EPlayerInputType input);

private:
	void SetCommandList();
public:
	virtual void BeginPlay() override;
	virtual void Hit(ECharacterCombatMontageType animtype) override;
protected:
	virtual void OnHitEnd() override;
	virtual int32 CalculateRecoveryStamina() override;
public:
	FChangeWeaponType OnChangeWeaponType;
private:
	FCommandListData commandListData;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponType, TObjectPtr<class UBaseCombatAnimationData>> weaponTypeAnimationData;	

	UPROPERTY()
	class UHFSMComponent* ownerHFSM;
};
