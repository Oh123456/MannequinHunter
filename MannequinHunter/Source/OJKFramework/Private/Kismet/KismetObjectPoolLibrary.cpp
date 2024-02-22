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
	SetActiveActor(actorObject, true);
	return actorObject;
}

bool UKismetObjectPoolLibrary::SetActor(AActor* actorObject)
{
	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	SetActiveActor(actorObject, false);
	return objectPoolManager->SetActor(actorObject);
}

void UKismetObjectPoolLibrary::SetActiveActor(AActor* actorObject, bool isEnable)
{
	// 액터를 감춤 
	actorObject->SetActorHiddenInGame(!isEnable);
	// 충돌 계산 비활성화
	actorObject->SetActorEnableCollision(isEnable);
	// 틱(업데이트 함수) 중지 
	actorObject->SetActorTickEnabled(isEnable);

}
