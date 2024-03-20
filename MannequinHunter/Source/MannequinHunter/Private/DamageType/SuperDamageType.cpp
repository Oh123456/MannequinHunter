// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageType/SuperDamageType.h"
#include "CombatSystem/CharacterCombatComponent.h"

float USuperDamageType::ExecuteDamageType(float damageAmount, UCombatComponent* damagedCombatSystem, AController* eventInstigator, AActor* damageCauser)
{
    if (damagedCombatSystem->IsA(UCharacterCombatComponent::StaticClass()))
    {
        UCharacterCombatComponent* characterCombat = Cast<UCharacterCombatComponent>(damagedCombatSystem);
        characterCombat->SetSuperArmor(false);
        return damageAmount * damageMultiplier;
    }
    return damageAmount;
}
