// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Status.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

struct FDeathInfo;
class ABaseWeapon;

USTRUCT(Blueprinttype)
struct FStatusDataTableBase : public FTableRowBase
{
	GENERATED_BODY()
};

USTRUCT(Blueprinttype)
struct FStatusDataTable : public FStatusDataTableBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FStatusDataBase statusDataBase;
};

UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class OJKFRAMEWORK_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam(UCombatComponent, FDeathEvent,const FDeathInfo&)
	DECLARE_EVENT_FiveParams(UCombatComponent, FTakeDamage, FStatus&, float, FDamageEvent const&, AController*, AActor*)
public:	
	// Sets default values for this component's properties
	UCombatComponent();
	virtual ~UCombatComponent();

	void ApplyDamage(UCombatComponent* damageComponent, AController* eventInstigator, AActor* damageCauser, TSubclassOf<UDamageType> damageTypeClass);
	virtual void TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser);

	inline void SetStatusData(const FStatusDataTable* table) { status.SetStatus(table); }
	inline const FStatus& GetStatus() {return status;}

	const FDeathEvent& OnDeath() { return deathEvent; }
	const FTakeDamage& OnTakeDamage() { return takeDamage; }

protected:
	virtual void BeginPlay() override;
	virtual float CalculateApplyDamage();
	// 소수점은 버림
	virtual int32 CalculateTakeDamage(float damageAmount);

private:
	FDeathEvent deathEvent;
	FTakeDamage takeDamage;
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStatusDataAsset> statusDataAsset;
	//UPROPERTY(EditDefaultsOnly)
	FStatus status;
private:
	UPROPERTY(EditDefaultsOnly)
	bool isImmortality;

};
