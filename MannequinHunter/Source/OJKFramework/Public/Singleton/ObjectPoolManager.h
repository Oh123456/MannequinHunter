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
				AActor* spawnActor = world->SpawnActor(instance);
				UE_LOG(Framework, Log, TEXT("Create Object Pool Item : %s "), *UKismetSystemLibrary::GetDisplayName(spawnActor))
				return spawnActor;
			}

			TObjectPtr<AActor> actor;

			obejcts.Dequeue(actor);
			UE_LOG(Framework, Log, TEXT("Get Object Pool Item : %s "), *UKismetSystemLibrary::GetDisplayName(actor))
			return actor;
		}
		void Set(AActor* item)
		{
			obejcts.Enqueue(item);
			UE_LOG(Framework, Log, TEXT("Set Object Pool Item : %s Item "), *UKismetSystemLibrary::GetDisplayName(item))
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

	class FObjectPoolKey
	{
		
	public:
		FObjectPoolKey(UClass* uclass)
		{
			uClass = uclass;
		}

		~FObjectPoolKey()
		{
			uClass = nullptr;
		}

		inline bool Equals(const FObjectPoolKey& key) const
		{
			UObject* uObject = Cast<UObject>(key.uClass.Get());
			if (uObject == nullptr)
				return false;
			return uObject->IsA(this->Get());
		}

		inline const UClass* Get() const
		{
			if (uClass == nullptr)
				return nullptr;

			return uClass.Get();

		}



	private:
		TWeakObjectPtr<UClass> uClass;
	};
	
	uint32 GetTypeHash(const FObjectPoolKey& key);

	inline bool operator == (const FObjectPoolKey& key, const FObjectPoolKey& key2)
	{
		return key.Equals(key2);
	}

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
	
	template<typename TUClass>
	TUClass* GetActor(TSubclassOf<AActor> actorClass)
	{
		return Cast<TUClass>(GetActor(actorClass));
	}

	AActor* GetActor(TSubclassOf<AActor> actorClass);
	bool SetActor(AActor* acotrObject);
private:
	TSharedPtr<FObjectPool> CreateObjectPool(const TSubclassOf<AActor>& actorClass);
private:

	UPROPERTY()
	TObjectPtr<UWorld> world;

	UPROPERTY()
	TMap<FObjectPoolKey, TSharedPtr<FObjectPool>> pools;
};


