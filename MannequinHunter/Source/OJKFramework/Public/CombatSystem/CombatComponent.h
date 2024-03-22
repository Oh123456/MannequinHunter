// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Status.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

struct FDeathInfo;
class ABaseWeapon;



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
	void ApplyPointDamage(UCombatComponent* damageComponent, float BaseDamage, const FVector& HitFromDirection, const FHitResult& HitInfo, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass);
	virtual void TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser);

	inline void SetStatusData(const struct FStatusDataTableBase* table) { status.SetStatus(table); }
	inline FStatus& GetStatusData() {return status;}

	FDeathEvent& OnDeath() { return deathEvent; }
	FTakeDamage& OnTakeDamage() { return takeDamage; }


	void SetImmortality(bool b) { isImmortality = b; }
	bool GetImmortality() const { return isImmortality; }
public:
	// Immortality Reset
	virtual void ClearStateData() { isImmortality = false; }
protected:
	virtual void BeginPlay() override;
	virtual float CalculateApplyDamage();
	// 소수점은 버림
	virtual int32 CalculateTakeDamage(float damageAmount);

private:
	FDeathEvent deathEvent;
	FTakeDamage takeDamage;
protected:
	FStatus status;
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> damageCauserActor;

	UPROPERTY(EditDefaultsOnly)
	bool isImmortality;

};
