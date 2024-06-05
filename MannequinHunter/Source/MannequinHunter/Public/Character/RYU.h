// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MannequinHunterPlayerCharacter.h"
#include "RYU.generated.h"

/**
 * 
 */

/*

*/

enum class EWeaponType : uint8;
enum class EPlayerInputType : uint8;

UCLASS()
class MANNEQUINHUNTER_API ARYU : public AMannequinHunterPlayerCharacter
{
	GENERATED_BODY()

	

public:
	ARYU();

protected:
	virtual void InputJumpKey() override;
	virtual void InputJumpKeyCompleted() override;

public:
	UFUNCTION(BlueprintCallable)
	void TestWeaponTypeChange(EWeaponType type);

public:
	virtual void Falling() override;
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

private:
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEquipment> weaponClass;
#ifdef UE_BUILD_DEBUG
	TSharedPtr<class FPlayerInputLog> playerInputLog;

public:
	const TSharedPtr<class FPlayerInputLog>& GetPlayerInputLog() { return playerInputLog; }
#endif
};
