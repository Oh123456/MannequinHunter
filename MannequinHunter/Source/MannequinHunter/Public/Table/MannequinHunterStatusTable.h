#pragma once

#include "CoreMinimal.h"
#include "Table/StatusTable.h"
#include "CombatSystem/MannequinHunterStatus.h"
#include "MannequinHunterStatusTable.generated.h"


USTRUCT(Blueprinttype)
struct MANNEQUINHUNTER_API FMannequinHunterStatusDataTable : public FStatusDataTableBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FMannequinHunterStatusData statusData;
};
