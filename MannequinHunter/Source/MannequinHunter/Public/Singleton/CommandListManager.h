// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Singleton.h"
#include "CombatSystem/CommandListTree.h"

enum class ERYUWeaponType : uint8;
enum class ECharacterCombatontageType : uint8;
enum class EPlayerInputType : uint8;
struct FCommandDataTable;

/**
 * 
 */
class MANNEQUINHUNTER_API FCommandListManager :public FSingleton<FCommandListManager>
{
public:
	FCommandListManager();
	virtual ~FCommandListManager();

	void LoadCommandListTable(const TMap<ERYUWeaponType, TObjectPtr<class UDataTable>>& table);

private:
	void AddCommandListTree(const TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatontageType>>& tree, const FCommandDataTable* table);
private:
	TMap<ERYUWeaponType, TSharedPtr<TCommandListTree<EPlayerInputType, ECharacterCombatontageType>>> commandList;
};
