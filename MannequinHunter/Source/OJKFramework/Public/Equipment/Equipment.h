// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"


UENUM()
enum class EEquipmentType
{
	E_Weapon,
};

UCLASS()
class OJKFRAMEWORK_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:	

	AEquipment() {}
	// Sets default values for this actor's properties
	AEquipment(EEquipmentType type);


protected:
	EEquipmentType equipmentType;
};
