#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CombatSystem/Status.h"
#include "StatusTable.generated.h"

USTRUCT(Blueprinttype)
struct OJKFRAMEWORK_API FStatusDataTableBase : public FTableRowBase
{
	GENERATED_BODY()
};

USTRUCT(Blueprinttype)
struct OJKFRAMEWORK_API FStatusDataTable : public FStatusDataTableBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FStatusDataBase statusDataBase;
};