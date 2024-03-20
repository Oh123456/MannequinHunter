// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActionGameDamageTypeInterface.generated.h"

class AController;
class AActor;
class UCombatComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActionGameDamageTypeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OJKFRAMEWORK_API IActionGameDamageTypeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float ExecuteDamageType(float damageAmount, UCombatComponent* damagedCombatSystem, AController* eventInstigator, AActor* damageCauser) { return damageAmount; };
};
