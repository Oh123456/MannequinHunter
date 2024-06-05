// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetObjectPoolLibrary.h"
#include "ObjectPool/ObjectPoolSubsystem.h"

void UKismetObjectPoolLibrary::SetWorld(AActor* worldActor)
{
	UObjectPoolSubsystem* objectPoolManager = GetObjectPoolManagerFromActor(worldActor);
	if (objectPoolManager)
	{
		objectPoolManager->ChangeWorld();
	}
}

AActor* UKismetObjectPoolLibrary::GetActor(UWorld* world, TSubclassOf<AActor> actorClass)
{
	UObjectPoolSubsystem* objectPoolManager = GetObjectPoolManagerFromWorld(world);
	AActor* actorObject = objectPoolManager->GetActor(actorClass);
	SetActiveActor(actorObject, true);
	return actorObject;
}

bool UKismetObjectPoolLibrary::SetActor(UWorld* world, AActor* actorObject)
{
	UObjectPoolSubsystem* objectPoolManager = GetObjectPoolManagerFromWorld(world);
	SetActiveActor(actorObject, false);
	return objectPoolManager->SetActor(actorObject);
}

void UKismetObjectPoolLibrary::SetActiveActor(AActor* actorObject, bool isEnable)
{
	// ���͸� ���� 
	actorObject->SetActorHiddenInGame(!isEnable);
	// �浹 ��� ��Ȱ��ȭ
	actorObject->SetActorEnableCollision(isEnable);
	// ƽ(������Ʈ �Լ�) ���� 
	actorObject->SetActorTickEnabled(isEnable);

}

UObjectPoolSubsystem* UKismetObjectPoolLibrary::GetObjectPoolManagerFromActor(AActor* worldActor)
{
	if (worldActor == nullptr)
		return nullptr;

	return worldActor->GetGameInstance()->GetSubsystem<UObjectPoolSubsystem>();
}

UObjectPoolSubsystem* UKismetObjectPoolLibrary::GetObjectPoolManagerFromWorld(UWorld* world)
{
	if (world == nullptr)
		return nullptr;

	return world->GetGameInstance()->GetSubsystem<UObjectPoolSubsystem>();
}
