#pragma once

#include "CombatSystem/CombatAnimationData.h"

enum class EPlayerCombatEnums : uint8
{
	NomalDodge = static_cast<uint8>(ECharacterCombatMontageType::Dodge1),
	CombatDodge = static_cast<uint8>(ECharacterCombatMontageType::Dodge2),
};


UENUM(BlueprintType)
enum class EPlayerStateEnum : uint8
{
	None = 0,
	Idle,
	Move,
	Sprint,
	Hit,
	Attack,
	Dodge,
	Jump,
	InputWait,

};


UENUM(BlueprintType)
enum class EPlayerStateMachine : uint8
{
	None = 0,
	Default,
	Falling,
	Hit,
	Combat = 1 << 7,
};


enum class EStateOrder : uint16
{
	None = 0,
	Idle,
	Attack,
	Dodge,
	Jump,
	InputWait,

	ToggleCombat = 1 << 8,
	Falling = 2 << 8,


	StateOrderBit = UINT8_MAX,
	StatemMachineOrderBit = UINT8_MAX << 8,
};

ENUM_CLASS_FLAGS(EStateOrder)

UENUM(BlueprintType)
enum class EPlayerInputType : uint8
{
	None = 0,
	LButton,
	RButton,
};



UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0,
	Katana = 1,
	Fist,

};