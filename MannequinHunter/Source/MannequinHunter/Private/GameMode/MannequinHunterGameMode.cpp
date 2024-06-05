// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/MannequinHunterGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "GameFramework/Character.h"
#include "Player/PlayerCharacter.h"
#include "HUD/MainUIWidget.h"
#include "ObjectPool/ObjectPoolSubsystem.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/SpawnTable.h"
#include "BaseActionCharacter.h"
#include "Components/CapsuleComponent.h"
#include "HUD/InventoryWidget.h"

AMannequinHunterGameMode::AMannequinHunterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> playerPawnBPClass(TEXT("/Game/BP/Character/Player/BP_RYU.BP_RYU_C"));
	if (playerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = playerPawnBPClass.Class;
	}
}

void AMannequinHunterGameMode::SpawnMonster(const FName& name, const FTransform& spawnTransform, bool isBoss)
{
	UObjectPoolSubsystem* objPool = GetGameInstance()->GetSubsystem<UObjectPoolSubsystem>();

	UTableSubsystem* table =  GetGameInstance()->GetSubsystem<UTableSubsystem>();
	FSpawnDataTable* data = table->GetTable<FSpawnDataTable>()->FindRow<FSpawnDataTable>(name,TEXT("Not Find SpawnData Table"));
	if (data)
	{
		APawn* actor = Cast<APawn>(objPool->GetActor(data->spawnActor));
		actor->SetActorLocation(spawnTransform.GetLocation());
		actor->SetActorRotation(spawnTransform.GetRotation());
		actor->SpawnDefaultController();

		if (isBoss)
		{
			spawnBoss = Cast<ABaseActionCharacter>(actor);

			spawnBoss->GetCombatComponent()->OnDeath().AddUObject(this, &AMannequinHunterGameMode::ClearBoss);
		}
	}
}

void AMannequinHunterGameMode::SetBossHUD()
{
	if (spawnBoss)
	{
		UCharacterCombatComponent* characterCombat = Cast<ABaseActionCharacter>(spawnBoss)->GetCombatComponent();
		FStatus& status = characterCombat->GetStatusData();

		status.OnChangeHPStatus.AddUObject(mainWidget, &UMainUIWidget::SetBossHPBar);

		mainWidget->SetBossHPBar(status.GetStatusData());

		mainWidget->SetWidgetVisibility(EMainUIWidgetEnum::BossHPBar, ESlateVisibility::Visible);
	}
}

void AMannequinHunterGameMode::ClearBossHUD()
{
	UCharacterCombatComponent* characterCombat = Cast<ABaseActionCharacter>(spawnBoss)->GetCombatComponent();
	FStatus& status = characterCombat->GetStatusData();

	status.OnChangeHPStatus.Clear();

	mainWidget->SetWidgetVisibility(EMainUIWidgetEnum::BossHPBar, ESlateVisibility::Hidden);
}

void AMannequinHunterGameMode::ToggleInventory()
{
	if (!inventoryWidget->IsInViewport())
	{
		inventoryWidget->AddToViewport();
	}
	else
	{
		inventoryWidget->RemoveFromParent();
	}
}


void AMannequinHunterGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (mainWidgetClass == nullptr)
		return;

	mainWidget = Cast<UMainUIWidget>(CreateWidget(GetWorld(), mainWidgetClass));
	inventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), inventoryWidgetClass));

	if (mainWidget)
	{
		mainWidget->AddToViewport();

	
		UCharacterCombatComponent* characterCombat = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetCombatComponent();
		FStatus& status = characterCombat->GetStatusData();
		
		status.OnChangeHPStatus.AddUObject(mainWidget, &UMainUIWidget::SetPlayerHPBar);
		status.OnChangeStaminaStatus.AddUObject(mainWidget, &UMainUIWidget::SetStaminaBar);
		
	}
}

void AMannequinHunterGameMode::ClearBoss(const FDeathInfo& info)
{
	ClearBossHUD();
	OnClearBossEvent.Broadcast(spawnBoss);
	spawnBoss->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	OnClearBossEvent.Clear();

	
	GetWorld()->GetTimerManager().SetTimer(bossClearTimerHandle, 
		[this]()
		{
			UObjectPoolSubsystem* objPool = GetGameInstance()->GetSubsystem<UObjectPoolSubsystem>();
			// 액터를 감춤 
			spawnBoss->SetActorHiddenInGame(true);
			// 충돌 계산 비활성화
			spawnBoss->SetActorEnableCollision(false);
			objPool->SetActor(spawnBoss);
			spawnBoss = nullptr;
		}, 2.0f, false);
}


