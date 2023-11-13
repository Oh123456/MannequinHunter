// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SoulslikeGameMode.h"

ASoulslikeGameMode::ASoulslikeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> playerPawnBPClass(TEXT("/Game/BP/Character/Player/BP_RYU.BP_RYU_C"));
	if (playerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = playerPawnBPClass.Class;
	}
}
