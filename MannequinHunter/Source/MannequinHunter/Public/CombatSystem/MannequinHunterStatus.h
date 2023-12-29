// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/Status.h"
#include "Table/statusTable.h"
#include "MannequinHunterStatus.generated.h"


/**
 * 
 */

USTRUCT(Blueprinttype)
struct FMannequinHunterStatusData : public FStatusData
{
	GENERATED_BODY()

	virtual ~FMannequinHunterStatusData() {};

	virtual void Copy(const FStatusDataBase& data) override
	{
		FStatusData::Copy(data);
	}
};

class MANNEQUINHUNTER_API FMannequinHunterStatus : FStatus
{

protected:
	virtual void CreateStatus() override;
	virtual const FStatusDataBase* GetStatusDataFormTable(const FStatusDataTableBase* dataTable) override;
};
