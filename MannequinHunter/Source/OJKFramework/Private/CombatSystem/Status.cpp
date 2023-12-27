// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/Status.h"
#include "CombatSystem/CombatComponent.h"
#include "CombatSystem/StatusDataAsset.h"


void FStatus::SetStatus(const FStatusDataTable* dataAsset)
{
	attack = dataAsset->attack;
	defensive = dataAsset->defensive;
	maxHealth = dataAsset->maxHealth;
	health = maxHealth;
}
