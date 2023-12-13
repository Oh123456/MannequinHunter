// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/ObjectPoolManager.h"

FObjectPoolManager::FObjectPoolManager()
{
}

FObjectPoolManager::~FObjectPoolManager()
{
	Clear();
	pools.Empty();
}

void FObjectPoolManager::Clear()
{
	for (const TPair<TObjectPtr< UClass>, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->Clear();
	}
}

void FObjectPoolManager::ChangeWorld(UWorld* newWorld)
{
	for (const TPair<TObjectPtr< UClass>, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->Clear();
		pair.Value->SetWorld(newWorld);
	}
}

void FObjectPoolManager::SetWorld(UWorld* newWorld)
{
	for (const TPair<TObjectPtr< UClass>, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->SetWorld(newWorld);
	}
}

AActor* FObjectPoolManager::GetActor(TSubclassOf<AActor> actorClass)
{
	TSharedPtr<FObjectPool>* findPool = pools.Find(actorClass->StaticClass());
	if (findPool == nullptr)
	{
		return CreateObjectPool(actorClass)->Get();
	}

	return (*findPool)->Get();
}

bool FObjectPoolManager::SetActor(AActor* acotrObject)
{
	TSharedPtr<FObjectPool>* findPool = pools.Find(acotrObject->StaticClass());
	if (findPool == nullptr)
		return false;

	(*findPool)->Set(acotrObject);
	return true;
}

TSharedPtr<FObjectPool> FObjectPoolManager::CreateObjectPool(TSubclassOf<AActor> actorClass)
{
	TSharedPtr<FObjectPool> pool = MakeShared<FObjectPool>(actorClass, world);
	pools.Add(actorClass->StaticClass(), pool);
	return pool;
}
