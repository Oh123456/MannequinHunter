// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "RYU.generated.h"

/**
 * 
 */

/*

*/

enum class EWeaponType : uint8;
enum class EPlayerInputType : uint8;

UCLASS()
class MANNEQUINHUNTER_API ARYU : public APlayerCharacter
{
	GENERATED_BODY()

	

public:
	ARYU();

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
	void Dodge(const struct FInputActionInstance& inputActionInstance);
	void LAttack(const struct FInputActionInstance& inputActionInstance);
	void RAttack(const struct FInputActionInstance& inputActionInstance);

	void Attack(EPlayerInputType type);

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
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* cameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* followCamera;

#ifdef UE_BUILD_DEBUG
	TSharedPtr<class FPlayerInputLog> playerInputLog;

public:
	const TSharedPtr<class FPlayerInputLog>& GetPlayerInputLog() { return playerInputLog; }
#endif
};
