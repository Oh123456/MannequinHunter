// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/KismetPlayerInputLogLibrary.h"
#include "Character/RYU.h"
#include "Character/PlayerCommonEnums.h"
#include "Utility/PlayerInputLog.h"

const TArray<EPlayerInputType> UKismetPlayerInputLogLibrary::GetPlayerInputs(ACharacter* character)
{
#ifdef UE_BUILD_DEBUG
	ARYU* player = Cast<ARYU>(character);
	if (player)
	{
		return player->GetPlayerInputLog()->GetPlayerInputs();
	}
#endif
	return TArray<EPlayerInputType>();
}
