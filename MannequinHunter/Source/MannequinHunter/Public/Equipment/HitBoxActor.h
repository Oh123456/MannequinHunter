// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitBoxActor.generated.h"

UCLASS()
class MANNEQUINHUNTER_API AHitBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitBoxActor();

	class UCapsuleComponent* GetHitBox() const { return hitBox; }

	void SetCylinderActive(bool isActive);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> hitBox;
};
