// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/ObjectPoolManager.h"
#include "GameFramework/Actor.h"
#include <typeinfo>

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
	for (const TPair<FObjectPoolKey, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->Clear();
	}
}

void FObjectPoolManager::ChangeWorld(UWorld* newWorld)
{
	world = newWorld;
	for (const TPair<FObjectPoolKey, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->Clear();
		pair.Value->SetWorld(newWorld);
	}
}

void FObjectPoolManager::SetWorld(UWorld* newWorld)
{
	world = newWorld;
	for (const TPair<FObjectPoolKey, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->SetWorld(newWorld);
	}
}

AActor* FObjectPoolManager::GetActor(TSubclassOf<AActor> actorClass)
{
	TSharedPtr<FObjectPool>* findPool = pools.Find(FObjectPoolKey(actorClass->StaticClass()));
	if (findPool == nullptr)
	{
		return CreateObjectPool(actorClass)->Get();
	}

	return (*findPool)->Get();
}

bool FObjectPoolManager::SetActor(AActor* actorObject)
{
	TSharedPtr<FObjectPool>* findPool = pools.Find(FObjectPoolKey(actorObject->StaticClass()));
	if (findPool == nullptr)
		return false;

	(*findPool)->Set(actorObject);
	return true;
}


TSharedPtr<FObjectPool> FObjectPoolManager::CreateObjectPool(const TSubclassOf<AActor>& actorClass)
{
	TSharedPtr<FObjectPool> pool = MakeShared<FObjectPool>(actorClass, world);
	pools.Add(FObjectPoolKey(actorClass->StaticClass()), pool);
	return pool;
}

uint32 OJKFramework::GetTypeHash(const FObjectPoolKey& key)
{
	uint32 Hash = FCrc::MemCrc32(&key, sizeof(FObjectPoolKey));
	return Hash;
}
