#include "CombatSystem/StatusComposite.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MannequinHunterPlayerCharacter.h"
#include "Subsystem/InventorySubsystem.h"
#include "Item/Item.h"

void FStatusComposite::AddComposite(const TSharedPtr<IStatusComposite>& composite)
{
	composites.Add(composite);
}


void FStatusComposite::GetStatusData(UWorld* worldObject, FMannequinHunterStatus& OUT characterStatus)
{
	FMannequinHunterStatusData statusData;

	for (TSharedPtr<IStatusComposite>& composite : composites)
	{
		composite->GetStatusData(worldObject , characterStatus);
	}
}

void FEquipmentComposite::GetStatusData(UWorld* worldObject, FMannequinHunterStatus& OUT characterStatus)
{
	TSharedPtr<FStatusData>& characterData = characterStatus.GetStatusData();

	UInventorySubsystem* inventory = worldObject->GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	const TMap<EEquipment, TSharedPtr<FItemData>>&  equipment = inventory->GetEquipment();

	for (auto& pair : equipment)
	{
		const TSharedPtr<FItemData>& data = pair.Value;
		if (data == nullptr)
			continue;

		const TSharedPtr<FEquipmentItemData> equipmentItem = StaticCastSharedPtr<FEquipmentItemData>(data);
		characterData->Sum(equipmentItem->GetStatusData());
	}
}
