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

	void SpawnBoos(const FName& name);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mainWidgetClass;

	UPROPERTY()
	TObjectPtr<class UMainUIWidget> mainWidget;
};



