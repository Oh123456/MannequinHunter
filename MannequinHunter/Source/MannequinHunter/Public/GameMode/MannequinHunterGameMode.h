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

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mainWidgetClass;
};



