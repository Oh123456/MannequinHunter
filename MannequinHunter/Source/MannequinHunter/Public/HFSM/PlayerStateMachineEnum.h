#pragma once


UENUM(BlueprintType)
enum class EPlayerStateMachine : uint8
{
	None = 0,
	Defulat,
	Falling,
	Hit,
	Combat = 1 << 7,
};
