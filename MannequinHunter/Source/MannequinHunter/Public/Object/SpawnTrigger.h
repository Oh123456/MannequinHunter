// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnTrigger.generated.h"

USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ASpawnPoint* spawnPoint;

	UPROPERTY(EditAnywhere)
	FName spawnName;

	UPROPERTY(EditAnywhere)
	bool isBoss = false;
};

UCLASS()
class MANNEQUINHUNTER_API ASpawnTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Spawn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SpawnMonster(class AMannequinHunterGameMode* gameMode);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> triggerComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = SpawnArctor)
	FSpawnData spawnData;


};
