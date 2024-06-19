// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ItemWidget.h"
#include "Components/Image.h"
#include "Subsystem/TableSubsystem.h"
#include "Subsystem/InventorySubsystem.h"
#include "Subsystem/UISubsystem.h"
#include "Table/ItemDataTable.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Input/Events.h"
#include "HUD/ItemInformationWidget.h"
#include "Kismet/GameplayStatics.h"


void UItemWidget::SetData(const FName& id)
{
	ItemID = const_cast<FName*>(&id);
	UGameInstance* gameInstance = GetGameInstance();
	UTableSubsystem* tableSubsystem = gameInstance->GetSubsystem<UTableSubsystem>();

	FItemDataTableResult result;
	tableSubsystem->GetItemTable(id , result);
	const UDataTable* itemTable = result.table;
	itemData = itemTable->FindRow<FItemTable>(id,TEXT(""));

	if (itemData == nullptr)
	{
		Clear();
		return;
	}

	iconWidget->SetBrushFromTexture(itemData->icon);
	iconWidget->SetColorAndOpacity(FLinearColor::White);
}

void UItemWidget::Clear()
{
	ItemID = nullptr;
	itemData = nullptr;
	iconWidget->SetBrushFromTexture(nullptr);
	FLinearColor color = FLinearColor::White;
	color.A = 0.0f;
	iconWidget->SetColorAndOpacity(color);
}

void UItemWidget::NativeOnInitialized()
{
	iconWidget = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	Clear();
}


void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (ItemID == nullptr || ItemID->IsNone())
		return;

	UUISubsystem* uiManager = GetGameInstance()->GetSubsystem<UUISubsystem>();

	activeInfoWidget = uiManager->Show<UItemInformationWidget>(TEXT("WBP_ItemInfo.WBP_ItemInfo_C"));

	activeInfoWidget->SetVisibility(ESlateVisibility::Hidden);
	activeInfoWidget->SetData(*GetItemData());

	GetWorld()->GetTimerManager().SetTimer(infoTimerHandle, [this]()
		{
			this->activeInfoWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			this->activeInfoWidget->ReSize(); 
		}, 0.01f, false);

}

FReply UItemWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply replay = Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	if (activeInfoWidget == nullptr)
		return replay;

	UGameViewportClient* viewportClient = GetWorld()->GetGameViewport();
	TSharedPtr<IGameLayerManager> gameLayerManager = viewportClient->GetGameLayerManager();
	const FGeometry& viewportGeometry = gameLayerManager->GetViewportWidgetHostGeometry();

	FVector2D viewportSize = viewportGeometry.GetLocalSize();

	FVector2D pos = InMouseEvent.GetScreenSpacePosition();
	FVector2D newPos;
	USlateBlueprintLibrary::LocalToViewport(this, InGeometry, infoWidgetOffset, pos, newPos);
	FVector2D widgetNewPos(newPos + InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()));

	FVector2D size = activeInfoWidget->GetCachedGeometry().GetLocalSize();

	//UE_LOG(LogTemp,Log,TEXT("%f %f") , widgetNewPos.X + size.X, widgetNewPos.Y + size.Y)

	if (widgetNewPos.X < 0)
	{
		widgetNewPos.X = 0;
	}
	else if (widgetNewPos.X + size.X > viewportSize.X)
	{
		int32 x = (widgetNewPos.X + size.X) - viewportSize.X;
		widgetNewPos.X -= x;
	}

	if (widgetNewPos.Y < 0)
	{
		widgetNewPos.Y = 0;
	}
	else if (widgetNewPos.Y + size.Y > viewportSize.Y)
	{
		int32 y = (widgetNewPos.Y + size.Y) - viewportSize.Y;
		widgetNewPos.Y -= y;
	}
	activeInfoWidget->SetPositionInViewport(widgetNewPos, false);
	return replay;
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (activeInfoWidget == nullptr)
		return;

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	if (timerManager.IsTimerActive(infoTimerHandle))
	{
		timerManager.ClearTimer(infoTimerHandle);
	}
	UUISubsystem* uiManager = GetGameInstance()->GetSubsystem<UUISubsystem>();

	uiManager->Hide(activeInfoWidget->GetClass());
	activeInfoWidget = nullptr;

}

const TSharedPtr<FItemData>* UItemWidget::GetItemData()
{
	return nullptr;
}
