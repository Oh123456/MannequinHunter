// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacterAnimInstance.h"
#include "HFSM/RYUHFSMComponent.h"
#include "RYUAnimInstance.generated.h"

/**
 * 
 */

UCLASS()
class MANNEQUINHUNTER_API URYUAnimInstance : public UPlayerCharacterAnimInstance
{
	GENERATED_BODY()
public:
	void SetIsInputJumpKey(bool b) { isInputJumpKey = b; }
public:
	UFUNCTION(BlueprintPure, Category = HFSM, meta = (BlueprintThreadSafe))
	bool IsCombat() { return (StaticCast<uint8>(ryuStateMachineState) & StaticCast<uint8>(EPlayerStateMachine::Combat)); }

private:
	UFUNCTION(BlueprintPure, Category = WeaponType , meta = (BlueprintThreadSafe))
	EWeaponType GetWeaponType();

	void Death(const FDeathInfo& deathInfo);
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaSeconds) override;
private:

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponType, int8> weaponTypeDeathCounts;

	UPROPERTY(BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	int32 deathAnimIndex;

	UPROPERTY(BlueprintReadOnly, Category = WeaponType, meta = (AllowPrivateAccess = "true"))
	EWeaponType weaponType;

	UPROPERTY(BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	EPlayerStateMachine ryuStateMachineState;

	UPROPERTY(BlueprintReadOnly, Category = InputState, meta = (AllowPrivateAccess = "true"))
	bool isInputJumpKey = false;

	UPROPERTY(BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	bool isDeath = false;


};
