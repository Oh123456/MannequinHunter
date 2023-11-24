// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetHFSMLibrary.h"
#include "HFSM/HFSMComponent.h"
#include "Player/PlayerCharacter.h"

uint8 UKismetHFSMLibrary::GetCurrentStateID(UHFSMComponent* hfsm)
{
	if (hfsm == nullptr)
		return 0;
	return hfsm->GetCurrentStateID();
}

uint8 UKismetHFSMLibrary::GetCurrentStateIDFromPlayerCharacter(APlayerCharacter* player)
{
	if (player == nullptr)
		return 0;

	return GetCurrentStateID(player->GetHFSM());
}

uint8 UKismetHFSMLibrary::GetCurrentStateMachineID(UHFSMComponent* hfsm)
{
	if (hfsm == nullptr)
		return 0;
	return hfsm->GetCurrentStateMachineID();
}

uint8 UKismetHFSMLibrary::GetCurrentStateMachineIDFromPlayerCharacter(APlayerCharacter* player)
{
	if (player == nullptr)
		return 0;

	return GetCurrentStateMachineID(player->GetHFSM());
}
