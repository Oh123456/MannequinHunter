#pragma once

#include "CombatSystem/CombatAnimationData.h"
#include "HFSM/States/PlayerStateEnum.h"

enum class EPlayerCombatEnums : uint8
{
	NomalDodge = static_cast<uint8>(ECharacterCombatontageType::Dodge1),
	CombatDodge = static_cast<uint8>(ECharacterCombatontageType::Dodge2),
};



enum class EStateOrder : uint16
{
	None = 0,
	Idle,
	Attack,
	Dodge,
	Jump,

	ToggleCombat = 1 << 8,



	StateOrderBit = UINT8_MAX,
	StatemMachineOrderBit = UINT8_MAX << 8,
};

ENUM_CLASS_FLAGS(EStateOrder)
