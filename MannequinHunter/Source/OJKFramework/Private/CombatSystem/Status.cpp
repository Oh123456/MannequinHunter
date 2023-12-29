// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/Status.h"
#include "CombatSystem/CombatComponent.h"
#include "CombatSystem/StatusDataAsset.h"
#include "Table/StatusTable.h"



void FStatus::SetStatus(const FStatusDataTableBase* dataTable) 
{
	if (status == nullptr)
		CreateStatus();

	const FStatusDataBase* data = GetStatusDataFormTable(dataTable);
	if (data)
		status->Copy(*data);
}

void FStatus::CreateStatus()
{
	status = MakeShared<FStatusData>();
}

const FStatusDataBase* FStatus::GetStatusDataFormTable(const FStatusDataTableBase* dataTable)
{
	const FStatusDataTable* table = StaticCast<const FStatusDataTable*>(dataTable);
	
	if (!table)
		return nullptr;

	return &table->statusDataBase;
}

void FStatusDataBase::Copy(const FStatusDataBase& data)
{
	attack = data.attack;
	attackSpeed = data.attackSpeed;
	defensive = data.defensive;
	maxHealth = data.maxHealth;
	maxStamina = data.maxStamina;
}

void FStatusData::Copy(const FStatusDataBase& data)
{
	FStatusDataBase::Copy(data);
	const FStatusData& statusData = static_cast<const FStatusData&>(data);

	health = statusData.health;
	stamina = statusData.stamina;

}
