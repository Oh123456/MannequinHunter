// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CombatSystem/CommandListTree.h"
#include "CommandListSubsystem.generated.h"

/**
 * 
 */

enum class EWeaponType : uint8;
enum class ECharacterCombatMontageType : uint8;
enum class EPlayerInputType : uint8;
struct FCommandDataTable;
struct FCommandData;

UCLASS()
class MANNEQUINHUNTER_API UCommandListSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void LoadCommandListTable(const class UDataTable* table);

	const TCommandListTree<EPlayerInputType, FCommandData>& GetCommandList() const { return commandList; }
private:
	void AddCommandListTree(const FCommandDataTable* table);
private:
	TCommandListTree<EPlayerInputType, FCommandData> commandList;
};
