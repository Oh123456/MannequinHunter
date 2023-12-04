// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Status.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

struct FDeathInfo;
class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OJKFRAMEWORK_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam(UCombatComponent,FDeathEvent,const FDeathInfo&)

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	virtual ~UCombatComponent();

	void ApplyDamage(UCombatComponent* damageComponent, AController* eventInstigator, AActor* damageCauser, TSubclassOf<UDamageType> damageTypeClass);
	virtual void TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser);

	inline const FStatus& GetStatus() {return status;}

	const FDeathEvent& OnDeath() { return deathEvent; }

protected:
	virtual void BeginPlay() override;
	virtual float CalculateApplyDamage();
	// 소수점은 버림
	virtual int32 CalculateTakeDamage(float damageAmount);

private:
	FDeathEvent deathEvent;
protected:
	UPROPERTY(EditDefaultsOnly)
	FStatus status;
private:
	UPROPERTY(EditDefaultsOnly)
	bool isImmortality;

	
};
