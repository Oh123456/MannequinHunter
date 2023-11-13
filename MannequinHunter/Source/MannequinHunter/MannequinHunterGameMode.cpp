// Copyright Epic Games, Inc. All Rights Reserved.

#include "MannequinHunterGameMode.h"
#include "MannequinHunterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMannequinHunterGameMode::AMannequinHunterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
