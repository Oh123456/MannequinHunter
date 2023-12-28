// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Status.generated.h"

struct FStatusDataTableBase;

USTRUCT(Blueprinttype)
struct FStatusDataBase
{
	GENERATED_BODY()

public:
	virtual void Copy(const FStatusDataBase& data);

public:
	UPROPERTY(EditDefaultsOnly)
	int32 attack;
	UPROPERTY(EditDefaultsOnly)
	int32 attackSpeed;
	UPROPERTY(EditDefaultsOnly)
	int32 defensive;
	UPROPERTY(EditDefaultsOnly)
	int32 maxHealth = 200;
	UPROPERTY(EditDefaultsOnly)
	int32 maxStamina;
};

USTRUCT(Blueprinttype)
struct OJKFRAMEWORK_API FStatusData : public FStatusDataBase
{
	GENERATED_BODY()
	virtual void Copy(const FStatusDataBase& data) override;

	int32 health;
	int32 stamina;
};


class OJKFRAMEWORK_API FStatus 
{
public:

	void SetStatus(const FStatusDataTableBase* dataTable);

	TSharedPtr<FStatusData>& GetStatus() {return status;}

protected:
	virtual void CreateStatus();
	virtual const FStatusDataBase* GetStatusDataFormTable(const FStatusDataTableBase* dataTable);
protected:
	TSharedPtr<FStatusData> status;
};
