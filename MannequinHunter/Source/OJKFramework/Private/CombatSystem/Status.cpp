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
	{
		status->Copy(*data);
		OnChangeStatus.Broadcast(status);
		OnChangeHPStatus.Broadcast(status);
		OnChangeStaminaStatus.Broadcast(status);		
	}
}

void FStatus::ChangeStatus(std::function<void(TSharedPtr<FStatusData>&)> fun)
{
	fun(status);
	OnChangeStatus.Broadcast(status);
}

void FStatus::AddHP(int32 addValue)
{
	status->health += addValue;
	if (CheckMaxHP())
		status->health = status->maxHealth;
	OnChangeHPStatus.Broadcast(status);
}

void FStatus::SetHP(int32 setValue)
{
	status->health = setValue;
	OnChangeHPStatus.Broadcast(status);
}

void FStatus::SetMaxHP(int32 setValue)
{
	status->maxHealth = setValue;
	OnChangeHPStatus.Broadcast(status);
}

void FStatus::AddStamina(int32 addValue)
{
	status->stamina += addValue;
	if (CheckMaxStamina())
		status->stamina = status->maxStamina;
	OnChangeStaminaStatus.Broadcast(status);
}

void FStatus::SetStamina(int32 setValue)
{
	status->stamina = setValue;
	OnChangeStaminaStatus.Broadcast(status);
}

void FStatus::SetMaxStamina(int32 setValue)
{
	status->maxStamina = setValue;
	OnChangeStaminaStatus.Broadcast(status);
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

	health = statusData.maxHealth;
	stamina = statusData.maxStamina;

}
