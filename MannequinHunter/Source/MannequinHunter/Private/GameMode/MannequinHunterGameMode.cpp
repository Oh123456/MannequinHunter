// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/MannequinHunterGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "GameFramework/Character.h"
#include "Player/PlayerCharacter.h"
#include "HUD/MainUIWidget.h"

AMannequinHunterGameMode::AMannequinHunterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> playerPawnBPClass(TEXT("/Game/BP/Character/Player/BP_RYU.BP_RYU_C"));
	if (playerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = playerPawnBPClass.Class;
	}
}


void AMannequinHunterGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (mainWidgetClass == nullptr)
		return;

	mainWidget = Cast<UMainUIWidget>(CreateWidget(GetWorld(), mainWidgetClass));

	if (mainWidget)
	{
		mainWidget->AddToViewport();

	
		UCharacterCombatComponent* characterCombat = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetCombatComponent();

		FStatus& status = characterCombat->GetStatusData();

		status.OnChangeHPStatus.AddUObject(mainWidget, &UMainUIWidget::SetHP);
		status.OnChangeStaminaStatus.AddUObject(mainWidget, &UMainUIWidget::SetStamina);
	}
}


