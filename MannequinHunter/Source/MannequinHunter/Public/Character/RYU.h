// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "RYU.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ERYUWeaponType : uint8
{
	None = 0,
	Katana = 1,
	Fist,

};

UCLASS()
class MANNEQUINHUNTER_API ARYU : public APlayerCharacter
{
	GENERATED_BODY()

	

public:
	ARYU();

	ERYUWeaponType GetWeaponType() { return weaponType; }
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return cameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return followCamera; }

private:
	void SetInputAction();

	void ToggleCombat();

	void InputJumpKey();
	void InputJumpKeyCompleted();
	void Dodge();
	void LAttack();
public:
	UFUNCTION(BlueprintCallable)
	void TestWeaponTypeChange(ERYUWeaponType type) { weaponType = type; }

public:
	virtual void Falling() override;
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();


private:
	ERYUWeaponType weaponType;
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* cameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* followCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TMap<ERYUWeaponType, TObjectPtr<class UCombatAnimationData>> weaponTypeAnimationData;
};
