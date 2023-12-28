// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Defines.h"
#include "Singleton/Singleton.h"

/**
 * 
 */

struct FStatusDataTable;

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
		TObjectPtr<UDataTable>* findTable = tables.FindByPredicate([](const TObjectPtr<UDataTable>& data)
			{
				return data->GetRowStruct()->IsChildOf(TTable::StaticStruct());
			});

		if (findTable == nullptr)
			return nullptr;

		return *findTable;
	}

	template<typename TTable>
	const TTable* GetTable(FName key, const FString& contextString = TEXT(""))
	{
		TObjectPtr<UDataTable>* findTable = tables.FindByPredicate([](const TObjectPtr<UDataTable>& data)
			{
				return data->GetRowStruct()->IsChildOf(TTable::StaticStruct());
			});

		if (findTable == nullptr)
			return nullptr;

		return (*findTable)->FindRow<TTable>(key, contextString);
	}
private:
	void LoadTable(const TCHAR* name);

private:
	UPROPERTY()
	TArray<TObjectPtr<UDataTable>> tables;
};
