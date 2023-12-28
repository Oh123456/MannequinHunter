// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/Status.h"

/**
 * 
 */


class MANNEQUINHUNTER_API FMannequinHunterStatus : FStatus
{
protected:
	virtual void CreateStatus() override;
	virtual const FStatusDataBase* GetStatusDataFormTable(const FStatusDataTableBase* dataTable) override;
};
