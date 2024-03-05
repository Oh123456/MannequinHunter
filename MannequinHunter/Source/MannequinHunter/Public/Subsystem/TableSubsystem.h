// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "TableSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UTableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:

	template<typename TTable>
	const UDataTable* GetTable()
	{
		TObjectPtr<UDataTable>* findTable = tableMap.Find(TTable::StaticStruct());

		if (findTable == nullptr)
			return nullptr;

		return *findTable;
	}


	template<typename TTable>
	const TTable* GetTable(FName key, const FString& contextString = TEXT(""))
	{
		TObjectPtr<UDataTable>* findTable = tableMap.Find(TTable::StaticStruct());

		if (findTable == nullptr)
			return nullptr;

		return (*findTable)->FindRow<TTable>(key, contextString);
	}

	template<typename TTable>
	void LoadTable(const TCHAR* name)
	{
		UDataTable* findTable = LoadObject<UDataTable>(nullptr, name);
		if (findTable)
		{
			tableMap.Add(TTable::StaticStruct(), findTable);
		}
	}
private:
	void LoadAIPatternDataTable();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	UPROPERTY()
	TMap<TObjectPtr<UStruct>, TObjectPtr<UDataTable>> tableMap;
};
