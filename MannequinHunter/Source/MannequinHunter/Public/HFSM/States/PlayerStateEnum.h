#pragma once

UENUM(BlueprintType)
enum class EPlayerStateEnum : uint8
{
	Idle = 0,
	Walk,
	Run,
	Sprint,
	Hit,
	Attack,
	Dodge,
	Jump,

};