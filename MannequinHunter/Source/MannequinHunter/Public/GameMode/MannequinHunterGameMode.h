// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MannequinHunterGameMode.generated.h"

UCLASS(minimalapi)
class AMannequinHunterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMannequinHunterGameMode();

	void SpawnMonster(const FName& name,const FTransform& spawnTransform, bool isBoss = false);

	void SetBossHUD();
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mainWidgetClass;

	UPROPERTY()
	TObjectPtr<class UMainUIWidget> mainWidget;

private:
	UPROPERTY()
	TObjectPtr<APawn> spawnBoss;
};



