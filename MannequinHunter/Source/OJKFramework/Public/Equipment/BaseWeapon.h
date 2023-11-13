// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/Equipment.h"
#include "CombatSystem/CombatComponent.h"
#include "BaseWeapon.generated.h"


DECLARE_DELEGATE(EHitCheckDelegate);
DECLARE_DELEGATE(EHitCheckBeginDelegate);
DECLARE_DELEGATE(EHitCheckEndDelegate);

USTRUCT()
struct FWeaponTraceHitParameter
{
	GENERATED_BODY()

	FWeaponTraceHitParameter()
	{
		startName = (TEXT("Hit_Start"));
		endName = (TEXT("Hit_End"));
		radius = 10.0f;
	}


	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (EditCondition = "bUseCylinder == false", EditConditionHides, AllowPrivateAccess = "true"));
	FName startName;

	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (EditCondition = "bUseCylinder == false", EditConditionHides, AllowPrivateAccess = "true"));
	FName endName;

	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (EditCondition = "bUseCylinder == false", EditConditionHides, AllowPrivateAccess = "true"));
	float radius;

	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (EditCondition = "bUseCylinder == false", EditConditionHides, AllowPrivateAccess = "true"));
	TArray<AActor*> ignoreActor;
};

UCLASS()
class OJKFRAMEWORK_API ABaseWeapon : public AEquipment
{
	GENERATED_BODY()
private:
	
	struct FAttackObject
	{
		FAttackObject(UCombatComponent* attackObject, int32 hitCount = 0)
		{
			this->attackObject = attackObject;
			this->hitCount = hitCount;
		}

		UPROPERTY()
		UCombatComponent* attackObject = nullptr;
		int32 hitCount = 0;
	};
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	inline void HitCheckBegin() { if (hitCheckBeginDelegate.IsBound()) hitCheckBeginDelegate.Execute(); }
	inline void HitCheck() { if (hitCheckDelegate.IsBound()) hitCheckDelegate.Execute(); }
	inline void HitCheckEnd() { if (hitCheckEndDelegate.IsBound()) hitCheckEndDelegate.Execute(); }

	void SetCylinderActive(bool isActive);
	
private:
	bool CheckHitAble(class UCombatComponent* damagedObject);
	void ApplyDamage(class UCombatComponent* damagedObject, const FHitResult& hitResult);
public:
	UFUNCTION()
	inline void ClearHitObjects() { attackObjects.Reset(0); }
	UFUNCTION(BlueprintCallable)
	void SetWeaponOwner(class AActor* weaponOwner);
private:
	UFUNCTION()
	void HitCheckCylinder(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void HitCheckTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	EHitCheckBeginDelegate hitCheckBeginDelegate;
	EHitCheckDelegate hitCheckDelegate;
	EHitCheckEndDelegate  hitCheckEndDelegate;

private:
	FVector startLocation;
	FVector endLocation;

	TArray<TSharedPtr<FAttackObject>> attackObjects;
protected:

	UPROPERTY(EditDefaultsOnly, Category = Cylinder)
	TObjectPtr<class UShapeComponent> cylinderComponent;
	UPROPERTY(EditDefaultsOnly, Category = Mesh);
	TObjectPtr<class UMeshComponent> weaponMeshComponent;

private:
	UPROPERTY()
	TObjectPtr<class ABaseActionCharacter> ownerCharacter;


	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (AllowPrivateAccess = "true"));
	TEnumAsByte<ETraceTypeQuery> attackAbleTraceType;

	// hit check use Cylinder? 
	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (AllowPrivateAccess = "true"));
	bool bUseCylinder;

	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (EditCondition = "bUseCylinder == false", EditConditionHides, AllowPrivateAccess = "true"))
	FWeaponTraceHitParameter weaponTraceHitParameter;

	// Number Of Attack Object
	// -1 Means there is no limit 
	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (AllowPrivateAccess = "true"))
	int8 numberOfAttackObject;
	// Number Of Attack Per Object
	// -1 Means there is no limit 
	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (AllowPrivateAccess = "true"))
	int8 numberOfAttackPerObject;
};
