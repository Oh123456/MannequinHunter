// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "Singleton/Singleton.h"

/**
 * 
 */

//struct FStatusDataTable;

class MANNEQUINHUNTER_API FTableManager
{
	DECLARE_SINGLETON(FTableManager)


private:
	FTableManager();
	~FTableManager();
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
private:
	//void LoadTable(const TCHAR* name);
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
	//UPROPERTY()
	//TArray<TObjectPtr<UDataTable>> tables;

	UPROPERTY()
	TMap<TObjectPtr<UStruct>, TObjectPtr<UDataTable>> tableMap;
};
