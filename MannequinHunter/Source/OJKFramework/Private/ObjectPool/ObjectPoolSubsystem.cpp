// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/ObjectPoolSubsystem.h"

void UObjectPoolSubsystem::Clear()
{
	for (const TPair<FObjectPoolKey, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->Clear();
	}
}

void UObjectPoolSubsystem::ChangeWorld()
{
	for (const TPair<FObjectPoolKey, TSharedPtr<FObjectPool>>& pair : pools)
	{
		pair.Value->Clear();
	}
}

AActor* UObjectPoolSubsystem::GetActor(TSubclassOf<AActor> actorClass)
{
	UWorld* world = GetWorld();
	TSharedPtr<FObjectPool>* findPool = pools.Find(FObjectPoolKey(actorClass->GetDefaultObject()->GetClass()));
	if (findPool == nullptr)
	{
		return CreateObjectPool(actorClass)->Get(world);
	}

	return (*findPool)->Get(world);
}

bool UObjectPoolSubsystem::SetActor(AActor* actorObject)
{
	TSharedPtr<FObjectPool>* findPool = pools.Find(FObjectPoolKey(actorObject->GetClass()));
	if (findPool == nullptr)
		return false;

	(*findPool)->Set(actorObject);
	return true;
}

TSharedPtr<FObjectPool> UObjectPoolSubsystem::CreateObjectPool(const TSubclassOf<AActor>& actorClass)
{
	TSharedPtr<FObjectPool> pool = MakeShared<FObjectPool>(actorClass);
	pools.Add(FObjectPoolKey(actorClass->GetDefaultObject()->GetClass()), pool);
	return pool;
}

uint32 OJKFramework::GetTypeHash(const FObjectPoolKey& key)
{
	uint32 Hash = FCrc::MemCrc32(&key, sizeof(FObjectPoolKey));
	return Hash;
}
