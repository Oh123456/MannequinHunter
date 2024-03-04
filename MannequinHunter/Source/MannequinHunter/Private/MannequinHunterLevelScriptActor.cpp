// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterLevelScriptActor.h"
#include "ObjectPool/ObjectPoolSubsystem.h"

void AMannequinHunterLevelScriptActor::Destroyed()
{
	Super::Destroyed();

	GetGameInstance()->GetSubsystem<UObjectPoolSubsystem>()->Clear();

	//FObjectPoolManager::GetInstance()->Clear();
}

void AMannequinHunterLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UObjectPoolSubsystem>()->ChangeWorld();
	//FObjectPoolManager::GetInstance()->ChangeWorld(GetWorld());
}
