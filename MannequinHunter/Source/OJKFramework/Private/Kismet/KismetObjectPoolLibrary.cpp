// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetObjectPoolLibrary.h"
#include "Singleton/ObjectPoolManager.h"

void UKismetObjectPoolLibrary::SetWorld(AActor* worldActor)
{
	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	objectPoolManager->ChangeWorld(worldActor->GetWorld());
}

AActor* UKismetObjectPoolLibrary::GetActor(TSubclassOf<AActor> actorClass)
{
	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	return objectPoolManager->GetActor(actorClass);
}

bool UKismetObjectPoolLibrary::SetActor(AActor* actorObject)
{
	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	return objectPoolManager->SetActor(actorObject);
}
