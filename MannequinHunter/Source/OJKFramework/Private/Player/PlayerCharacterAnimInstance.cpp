// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterAnimInstance.h"


void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	

	APlayerCharacter* playerCharacter = StaticCast<APlayerCharacter*>(ownerCharacter);
	if (playerCharacter)
	{
		isInputMoveKey = playerCharacter->IsMoveInput();
	}

}
