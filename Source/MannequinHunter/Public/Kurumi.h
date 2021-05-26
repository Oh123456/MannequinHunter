// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Kurumi.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API AKurumi : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AKurumi();


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* followCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapone, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* weapone;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapone, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* sheath;
};
