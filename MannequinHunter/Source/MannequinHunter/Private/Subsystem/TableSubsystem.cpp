// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/TableSubsystem.h"
#include "Table/MannequinHunterStatusTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "AI/AIPatternTable.h"
#include "Table/SpawnTable.h"
#include "Table/ActionDataTable.h"
#include "Table/ItemDataTable.h"

const TCHAR* AIPatternPath = TEXT("/Game/BP/DataTable/AIPatternDataTables/");

const FName UTableSubsystem::STRINGTABLE_UI_PATH = TEXT("/Game/BP/DataTable/ST_UI.ST_UI");
const FName UTableSubsystem::STRINGTABLE_ITEM_PATH = TEXT("/Game/BP/DataTable/ST_Item.ST_Item");

const UDataTable* UTableSubsystem::LoadAIPatternTable(const FName& tableName)
{
	FString path = AIPatternPath;
	path.Append(tableName.ToString());
	return LoadObject<UDataTable>(nullptr, (*path));
}

const void UTableSubsystem::GetItemTable(const FName& id, FItemDataTableResult& OUT itemDataTableResult)
{
	const FItemKeyTable* keytable = GetTable<FItemKeyTable>()->FindRow<FItemKeyTable>(id,TEXT(""));
	itemDataTableResult.table = nullptr;
	itemDataTableResult.type = EItemType::E_Etc;
	if (keytable == nullptr)
		return;

	itemDataTableResult.type = keytable->itemType;

	switch (keytable->itemType)
	{
	case EItemType::E_Etc:
		itemDataTableResult.table = GetTable<FItemTable>();
		break;
	case EItemType::E_Equipment:
		itemDataTableResult.table = GetTable<FEquipmentItemTable>();
		break;
	case EItemType::E_Weapon:
		itemDataTableResult.table = GetTable<FWeaponItemTable>();
		break;
	default:
		break;
	}
		
}

void UTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

	LoadTable<FMannequinHunterStatusDataTable>(TEXT("/Game/BP/DataTable/DT_StatuesData"));
	LoadTable<FCommandDataTable>(TEXT("/Game/BP/DataTable/DT_Command"));
	LoadTable<FAIPatternTreeTable>(TEXT("/Game/BP/DataTable/DT_AIPatternTree"));
	LoadTable<FSpawnDataTable>(TEXT("/Game/BP/DataTable/DT_SpawnTable.DT_SpawnTable"));
	LoadTable<FActionTable>(TEXT("/Game/BP/DataTable/DT_ActionTable.DT_ActionTable"));
	LoadTable<FItemKeyTable>(TEXT("/Game/BP/DataTable/DT_ItemKey"));
	LoadTable<FItemTable>(TEXT("/Game/BP/DataTable/DT_Item"));
	LoadTable<FEquipmentItemTable>(TEXT("/Game/BP/DataTable/DT_EquipmentItem"));
	LoadTable<FWeaponItemTable>(TEXT("/Game/BP/DataTable/DT_WeaponItem"));
}

void UTableSubsystem::Deinitialize()
{
	tableMap.Empty();
}
