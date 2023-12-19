// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinHunterLevelScriptActor.h"
#include "Singleton/ObjectPoolManager.h"

void AMannequinHunterLevelScriptActor::Destroyed()
{
	Super::Destroyed();

	FObjectPoolManager::GetInstance()->Clear();
}

void AMannequinHunterLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	FObjectPoolManager::GetInstance()->ChangeWorld(GetWorld());
}
