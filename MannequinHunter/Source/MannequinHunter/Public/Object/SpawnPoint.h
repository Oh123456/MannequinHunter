// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class MANNEQUINHUNTER_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();
private:
	UPROPERTY()
	TObjectPtr<class UCapsuleComponent> capsuleComponent;
#if WITH_EDITORONLY_DATA


	UPROPERTY(EditAnywhere)
	TObjectPtr<class UArrowComponent> arrowComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBillboardComponent> sprite;

#endif

};
