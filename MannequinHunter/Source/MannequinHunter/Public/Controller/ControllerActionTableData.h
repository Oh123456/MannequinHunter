// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ControllerActionTableData.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UControllerActionTableData : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MANNEQUINHUNTER_API IControllerActionTableData
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetActionTableData(const FName& actionName) {}
	virtual void ClearTable() {}
	virtual const struct FActionTable* GetActionTableData() const { return nullptr; }
};
