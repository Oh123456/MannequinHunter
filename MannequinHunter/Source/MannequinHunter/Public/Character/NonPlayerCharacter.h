// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionCharacter.h"
#include "NonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API ANonPlayerCharacter : public ABaseActionCharacter 
{
	GENERATED_BODY()
public:
	template<typename TKey>
	void SetState(TKey state) { SetBlackBoardState(static_cast<uint8>(state)); }
	void SetBlackBoardState(uint8 state);

protected:
	uint8 currentState = 0;

};
