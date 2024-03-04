// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Character/PlayerCommonEnums.h"
#include "StateSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	uint8 GetStateID(EStateOrder order);
	template<typename T>
	uint8 GetStateID(T tOrder) { return GetStateID(StaticCast<EStateOrder>(tOrder)); }

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
private:
	TMap<EStateOrder, uint8> stateDataMap;
};
