// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/KismetPlayerInputLogLibrary.h"
#include "Character/RYU.h"
#include "Character/PlayerCommonEnums.h"
#include "Utility/PlayerInputLog.h"

FString UKismetPlayerInputLogLibrary::GetPlayerInputs(ACharacter* character)
{
	FString string;
#ifdef UE_BUILD_DEBUG
	ARYU* player = Cast<ARYU>(character);
	if (player)
	{
		const TArray<EPlayerInputType>& array = player->GetPlayerInputLog()->GetPlayerInputs();

		const UEnum* uenum = FindFirstObjectSafe<UEnum>(TEXT("EPlayerInputType"));

		string.Append(TEXT("InputString : "));
		for (EPlayerInputType type : array)
		{

			string.Append(uenum->GetDisplayNameTextByValue(StaticCast<int32>(type)).ToString());
			string.Append(TEXT(", "));
		}

	}
#endif
	return string;
}
