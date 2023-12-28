// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Singleton/Singleton.h"
#include "CombatSystem/CommandListTree.h"

enum class EWeaponType : uint8;
enum class ECharacterCombatMontageType : uint8;
enum class EPlayerInputType : uint8;
struct FCommandDataTable;

/**
 * 
 */
class MANNEQUINHUNTER_API FCommandListManager 
{
	DECLARE_SINGLETON(FCommandListManager);

	FCommandListManager();
	~FCommandListManager();
public:
	void LoadCommandListTable(const class UDataTable* table);

	const TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>& GetCommandList() const { return commandList; }
private:
	void AddCommandListTree(const FCommandDataTable* table);

private:
	TCommandListTree<EPlayerInputType, ECharacterCombatMontageType> commandList;
//	void LoadCommandListTable(const TMap<EWeaponType, TObjectPtr<class UDataTable>>& table);
//
//	const TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>>* GetCommandList(EWeaponType weaponType) const;
//private:
//	void AddCommandListTree(const TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>>& tree, const FCommandDataTable* table);

	//TMap<EWeaponType, TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatMontageType>>> commandListMap;

};
