#pragma once

#include "CombatSystem/CombatAnimationData.h"
#include "HFSM/States/PlayerStateEnum.h"

enum class EPlayerCombatEnums : uint8
{
	NomalDodge = static_cast<uint8>(ECharacterCombatontageType::Dodge1),
	CombatDodge = static_cast<uint8>(ECharacterCombatontageType::Dodge2),
};