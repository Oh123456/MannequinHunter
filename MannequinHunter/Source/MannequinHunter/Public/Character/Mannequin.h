// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEnemyCharacter.h"
#include "Mannequin.generated.h"

UCLASS()
class MANNEQUINHUNTER_API AMannequin : public ABaseEnemyCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEquipment> weaponClass;
};
