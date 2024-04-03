// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MannequinHunterGameMode.generated.h"

DECLARE_EVENT_OneParam(AMannequinHunterGameMode, FClearBoss, class ABaseActionCharacter*);

struct FDeathInfo;

UCLASS(minimalapi)
class AMannequinHunterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMannequinHunterGameMode();

	void SpawnMonster(const FName& name,const FTransform& spawnTransform, bool isBoss = false);

	void SetBossHUD();
	void ClearBossHUD();
protected:
	virtual void BeginPlay() override;

private:
	void ClearBoss(const FDeathInfo& info);
public:
	FClearBoss OnClearBossEvent;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> mainWidgetClass;

	UPROPERTY()
	TObjectPtr<class UMainUIWidget> mainWidget;

private:
	UPROPERTY()
	TObjectPtr<class ABaseActionCharacter> spawnBoss;


	FTimerHandle bossClearTimerHandle;
};



