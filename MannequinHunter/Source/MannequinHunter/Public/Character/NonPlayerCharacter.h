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
	template<typename TEnum>
	void SetState(TEnum state) { SetState(static_cast<uint8>(state)); }
	void SetState(uint8 state) { currentState = state; }
	bool IsState(uint8 state) const { return state == currentState; }

protected:
	uint8 currentState = 0;

};
