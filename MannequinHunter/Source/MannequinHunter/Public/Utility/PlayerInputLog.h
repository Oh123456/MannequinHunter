// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
enum class EPlayerInputType : uint8;
/**
 * 
 */
class MANNEQUINHUNTER_API FPlayerInputLog
{
public:
	FPlayerInputLog();
	~FPlayerInputLog();

	void AddPlayerInput(EPlayerInputType type) { playerInputs.Add(type); }
	void ResetPlayerInputs() { playerInputs.Reset(); }

	const TArray<EPlayerInputType>& GetPlayerInputs() const { return playerInputs; }
private:
	TArray<EPlayerInputType> playerInputs;
};
