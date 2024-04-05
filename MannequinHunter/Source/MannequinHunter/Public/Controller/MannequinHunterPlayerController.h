// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/ActionPlayerController.h"
#include "ControllerActionTableData.h"
#include "MannequinHunterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API AMannequinHunterPlayerController : public AActionPlayerController , public IControllerActionTableData
{
	GENERATED_BODY()
public:
	virtual void SetActionTableData(const FName& actionName) override;
	virtual void ClearTable() override { UE_LOG(LogTemp,Log,TEXT("Clear!!!")) tableData = nullptr; }
	virtual const struct FActionTable* GetActionTableData() const override { return tableData; }
protected:
	virtual void BeginPlay() override;
private:
	const class UDataTable* actionTable;

	const struct FActionTable* tableData;
};
