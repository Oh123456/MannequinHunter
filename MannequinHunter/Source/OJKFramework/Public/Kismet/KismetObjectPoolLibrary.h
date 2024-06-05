// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KismetObjectPoolLibrary.generated.h"


UCLASS()
class OJKFRAMEWORK_API UKismetObjectPoolLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, DisplayName = "Set ObjectPool World")
	static void SetWorld(AActor* worldActor);

	UFUNCTION(BlueprintCallable, DisplayName = "Get ObjectPool Actor")
	static class AActor* GetActor(UWorld* world, TSubclassOf<AActor> actorClass);

	UFUNCTION(BlueprintCallable, DisplayName = "Set ObjectPool Actor")
	static bool SetActor(UWorld* world, AActor* actorObject);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Active Actor")
	static void SetActiveActor(AActor* actorObject, bool isEnable);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Object Pool Manager(WorldActor)")
	static class UObjectPoolSubsystem* GetObjectPoolManagerFromActor(AActor* worldActor);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Object Pool Manager(World)")
	static class UObjectPoolSubsystem* GetObjectPoolManagerFromWorld(class UWorld* world);
};
