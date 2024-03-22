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
	virtual ~FStatusDataBase() {};
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

	virtual ~FStatusData() {};

	virtual void Copy(const FStatusDataBase& data) override;

	int32 health;
	int32 stamina;
};


class OJKFRAMEWORK_API FStatus 
{
public:
	DECLARE_EVENT_OneParam(FStatus, FOnChangeStatus, const TSharedPtr<FStatusData>&)
public:
	virtual ~FStatus() {}

	void SetStatus(const FStatusDataTableBase* dataTable);

	//TSharedPtr<FStatusData>& GetStatusData() {return status;}

	void ChangeStatus(std::function<void(TSharedPtr<FStatusData>&)> fun);

	void AddHP(int32 addValue);
	void SetHP(int32 setValue);
	void SetMaxHP(int32 setValue);

	void AddStamina(int32 addValue);
	void SetStamina(int32 setValue);
	void SetMaxStamina(int32 setValue);	

	bool CheckStamina() const { return status->stamina > 0; }
	bool CheckMaxStamina() const { return status->maxStamina <= status->stamina; }
	bool CheckMaxHP() const { return status->maxHealth <= status->health; }

	const TSharedPtr<FStatusData>& GetStatusData() const { return status; }
protected:
	virtual void CreateStatus();
	virtual const FStatusDataBase* GetStatusDataFormTable(const FStatusDataTableBase* dataTable);
public:
	// HP,Stamina Exception Chanage Call Event
	FOnChangeStatus OnChangeStatus;
	FOnChangeStatus OnChangeHPStatus;
	FOnChangeStatus OnChangeStaminaStatus;
protected:
	TSharedPtr<FStatusData> status;
};
