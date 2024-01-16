// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KismetCombatSystemLibrary.generated.h"


class AEquipment;
class ABaseWeapon;
class UCharacterCombatComponent;
class ABaseActionCharacter;
class APlayerCharacter;


/**
 * 
 */
UCLASS(meta = (BlueprintThreadSafe, ScriptName = "CombatSystemLibrary"))
class OJKFRAMEWORK_API UKismetCombatSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	static AEquipment* CreateMainWeapon(UCharacterCombatComponent* characterCombat,TSubclassOf<ABaseWeapon> staticClass);

	UFUNCTION(BlueprintPure)
	static int32 GetAttackCount(UCharacterCombatComponent* characterCombat);

	UFUNCTION(BlueprintPure)
	static int32 GetAttackCountFromPlayer(APlayerCharacter* player);
};
