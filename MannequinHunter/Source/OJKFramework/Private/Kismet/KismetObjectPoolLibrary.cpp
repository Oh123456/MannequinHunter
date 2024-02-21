// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetObjectPoolLibrary.h"
#include "ObjectPool/ObjectPoolManager.h"

void UKismetObjectPoolLibrary::SetWorld(AActor* worldActor)
{
	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	objectPoolManager->ChangeWorld(worldActor->GetWorld());
}

AActor* UKismetObjectPoolLibrary::GetActor(TSubclassOf<AActor> actorClass)
{
	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	AActor* actorObject = objectPoolManager->GetActor(actorClass);
	actorObject->SetActorHiddenInGame(false);
	return actorObject;
}

bool UKismetObjectPoolLibrary::SetActor(AActor* actorObject)
{
	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	actorObject->SetActorHiddenInGame(true);
	return objectPoolManager->SetActor(actorObject);
}
