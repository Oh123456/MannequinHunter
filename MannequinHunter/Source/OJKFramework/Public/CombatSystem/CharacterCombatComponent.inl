#pragma once
#include "CharacterCombatComponent.h"


inline AEquipment* FEquipmentItem::GetEquipment(int32 intdex)
{
	return equipment;
}

inline void FEquipmentItem::SetEquipment(int32 intdex, AEquipment* newequipment)
{
	this->equipment = newequipment;
}

inline AEquipment* FEquipmentItems::GetEquipment(int32 intdex)
{
	return equipments[intdex];
}

inline void FEquipmentItems::SetEquipment(int32 intdex, AEquipment* equipment)
{
	if (equipments.Num() <= intdex)
		equipments.Add(equipment);
	equipments[intdex] = equipment;
}



inline void UCharacterCombatComponent::AddCombatAbleFlag(ECombatAble combatAble)
{
	this->characterCombatData.combatAbleFlag = static_cast<ECombatAble>(this->characterCombatData.combatAbleFlag | combatAble);
}

inline void UCharacterCombatComponent::SubtractCombatAbleFlag(ECombatAble combatAble)
{
	this->characterCombatData.combatAbleFlag = static_cast<ECombatAble>(this->characterCombatData.combatAbleFlag & ~combatAble);
}

inline void UCharacterCombatComponent::AddCombatAbleFlag(int32 combatAble)
{
	this->characterCombatData.combatAbleFlag = static_cast<ECombatAble>(this->characterCombatData.combatAbleFlag | combatAble);
}

inline void UCharacterCombatComponent::SubtractCombatAbleFlag(int32 combatAble)
{
	this->characterCombatData.combatAbleFlag = static_cast<ECombatAble>(this->characterCombatData.combatAbleFlag & ~combatAble);
}


inline void UCharacterCombatComponent::SetIsActorRotation(bool b)
{
	this->characterRotationData.isActorRotation = b;
}




template<typename TEquipmentItems>
AEquipment* UCharacterCombatComponent::CreateEquipment(TSubclassOf<AEquipment> createEquipment, ECombatEquipmentSlot slot, int32 addIndex)
{
	TSharedPtr<IEquipmentItem>* findItem = characterCombatData.equipmentItem.Find(slot);

	if (findItem == nullptr)
	{
		TSharedPtr<IEquipmentItem> newObejct = MakeShared<FEquipmentItem>();

		characterCombatData.equipmentItem.Add(slot, newObejct);

		findItem = &newObejct;
	}

	AEquipment* createObject = GetWorld()->SpawnActor<AEquipment>(createEquipment);
	(*findItem)->SetEquipment(addIndex, createObject);

	return createObject;
}

inline AEquipment* UCharacterCombatComponent::GetEquipment(ECombatEquipmentSlot slot, int32 index)
{
	TSharedPtr<IEquipmentItem>* findItem = characterCombatData.equipmentItem.Find(slot);

	if (findItem == nullptr)
		return nullptr;

	return (*findItem)->GetEquipment(index);
}