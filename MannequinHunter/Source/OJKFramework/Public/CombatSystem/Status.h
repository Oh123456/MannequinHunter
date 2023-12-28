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

struct FStatusData : FStatusDataBase
{
	virtual void Copy(const FStatusDataBase& data) override;

	int32 health;
	int32 stamina;
};


USTRUCT(BlueprintType)
struct OJKFRAMEWORK_API FStatus 
{
	GENERATED_BODY()
public:

	void SetStatus(const FStatusDataTableBase* dataTable);

	TSharedPtr<FStatusData>& GetStatus() {return status;}

protected:
	virtual void CreateStatus();
	virtual const FStatusDataBase* GetStatusDataFormTable(const FStatusDataTableBase* dataTable);
private:
	TSharedPtr<FStatusData> status;
};
