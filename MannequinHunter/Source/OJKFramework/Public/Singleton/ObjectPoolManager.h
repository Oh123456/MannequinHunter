// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Singleton.h"
#include "Containers/Queue.h"
#include "OJKFramework.h"
#include "Kismet/KismetSystemLibrary.h"


/**
 * 
 */

namespace OJKFramework
{

	class FObjectPool 
	{
	public:
		FObjectPool(TSubclassOf<AActor> actor) { instance = actor; };
		FObjectPool(TSubclassOf<AActor> actor ,UWorld* newWorld)
		{ 
			instance = actor;
			world = newWorld;
			UE_LOG(Framework, Log, TEXT("Create Object Pool : %s "), *UKismetSystemLibrary::GetDisplayName(actor));
		}
		~FObjectPool() { Clear(); };

	public:
		AActor* Get()
		{
			if (world == nullptr)
				return nullptr;
			if (obejcts.IsEmpty())
			{
				return world->SpawnActor(instance);
				UE_LOG(Framework, Log, TEXT("Create Object Pool Itme : %s "), *UKismetSystemLibrary::GetDisplayName(instance))
			}

			TObjectPtr<AActor> actor;

			obejcts.Dequeue(actor);
			UE_LOG(Framework, Log, TEXT("Get Object Pool Itme : %s "), *UKismetSystemLibrary::GetDisplayName(instance))
			return actor;
		}
		void Set(AActor* item)
		{
			obejcts.Enqueue(item);
			UE_LOG(Framework, Log, TEXT("Set Object Pool Itme : %s Item "), *UKismetSystemLibrary::GetDisplayName(item))
		}

		void SetWorld(UWorld* newWorld) { world = newWorld; }
		void Clear() { obejcts.Empty(); world = nullptr; }
	private:
		UPROPERTY()
		TQueue<TObjectPtr<AActor>> obejcts;

		UPROPERTY()
		TObjectPtr<UWorld> world;

		UPROPERTY()
		TSubclassOf<AActor> instance;
	};
}

using namespace OJKFramework;
class AActor;
class UWorld;

class OJKFRAMEWORK_API FObjectPoolManager 
{
	DECLARE_SINGLETON(FObjectPoolManager);

	FObjectPoolManager();
	~FObjectPoolManager();
public:
	
	void Clear();
	void ChangeWorld(UWorld* newWorld);
	// юс╫ц 
	void SetWorld(UWorld* newWorld);
	
	AActor* GetActor(TSubclassOf<AActor> actorClass);
	bool SetActor(AActor* acotrObject);
private:
	TSharedPtr<FObjectPool> CreateObjectPool(TSubclassOf<AActor> actorClass);
private:

	UPROPERTY()
	TObjectPtr<UWorld> world;

	UPROPERTY()
	TMap<TObjectPtr<UClass>, TSharedPtr<FObjectPool>> pools;
};


