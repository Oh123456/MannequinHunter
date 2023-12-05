// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MannequinHunterGameInstance.generated.h"

/**
 * 
 */
enum class ERYUWeaponType : uint8;


UCLASS()
class MANNEQUINHUNTER_API UMannequinHunterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void OnStart() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TMap<ERYUWeaponType,TObjectPtr<class UDataTable>> commendDataTable;
};
