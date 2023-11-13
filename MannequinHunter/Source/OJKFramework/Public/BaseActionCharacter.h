// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseActionCharacter.generated.h"

class UCharacterCombatComponent;

UCLASS()
class OJKFRAMEWORK_API ABaseActionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseActionCharacter();

	inline UCharacterCombatComponent* GetCombatComponent() { return combatComponent; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCharacterCombatComponent> combatComponent;
};
