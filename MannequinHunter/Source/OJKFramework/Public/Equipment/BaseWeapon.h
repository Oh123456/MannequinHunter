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

USTRUCT()
struct FWeaponHitData
{
	GENERATED_BODY()

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



	// Number Of Attack Object
	// -1 Means there is no limit 
	UPROPERTY(EditDefaultsOnly, Category = HitSystem)
	int8 numberOfAttackObject = -1;
	// Number Of Attack Per Object
	// -1 Means there is no limit 
	UPROPERTY(EditDefaultsOnly, Category = HitSystem)
	int8 numberOfAttackPerObject = 1;

	UPROPERTY(EditDefaultsOnly, Category = HitSystem);
	TEnumAsByte<ETraceTypeQuery> attackAbleTraceType = ETraceTypeQuery::TraceTypeQuery1;

	FVector hitDirectionStartLocation;

	FVector startLocation;
	FVector endLocation;

	TArray<TSharedPtr<FAttackObject>> attackObjects = {};
};

struct FBaseWeaponData
{

	UPROPERTY()
	TObjectPtr<class ABaseActionCharacter> ownerCharacter;
};

UCLASS()
class OJKFRAMEWORK_API ABaseWeapon : public AEquipment
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	inline void HitCheckBegin() { if (hitCheckBeginDelegate.IsBound()) hitCheckBeginDelegate.Execute(); }
	inline void HitCheck() { if (hitCheckDelegate.IsBound()) hitCheckDelegate.Execute(); }
	inline void HitCheckEnd() { if (hitCheckEndDelegate.IsBound()) hitCheckEndDelegate.Execute(); }

	
private:
	bool CheckHitAble(class UCombatComponent* damagedObject);
	void ApplyDamage(class UCombatComponent* damagedObject, const FHitResult& hitResult);
public:
	UFUNCTION()
	inline void ClearHitObjects() { weaponHitData.attackObjects.Reset(0); }
	UFUNCTION(BlueprintCallable)
	virtual void SetWeaponOwner(class AActor* weaponOwner);
protected:
	UFUNCTION()
	virtual void HitCheckCylinder(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	virtual void HitCheckTrace();
public:
	virtual void SetCylinderActive(bool isActive);
	virtual FVector2D GetAttackDirection() const;
	virtual FVector GetHitPoint() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetCylinder();
	virtual void SetTraceHit();
	virtual bool CheckCylinderComponent();

protected:
	EHitCheckBeginDelegate hitCheckBeginDelegate;
	EHitCheckDelegate hitCheckDelegate;
	EHitCheckEndDelegate  hitCheckEndDelegate;
private:
	FBaseWeaponData weaponData;
protected:

	UPROPERTY(EditDefaultsOnly, Category = Cylinder)
	TObjectPtr<class UShapeComponent> cylinderComponent;
	UPROPERTY(EditDefaultsOnly, Category = Mesh);
	TObjectPtr<class UMeshComponent> weaponMeshComponent;

protected:
	UPROPERTY(EditDefaultsOnly, Category = HitSystem);
	FWeaponHitData weaponHitData;
	// hit check use Cylinder? 
	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (AllowPrivateAccess = "true"));
	bool bUseCylinder = true;
private:
	UPROPERTY(EditDefaultsOnly, Category = HitSystem, meta = (EditCondition = "bUseCylinder == false", EditConditionHides, AllowPrivateAccess = "true"))
	FWeaponTraceHitParameter weaponTraceHitParameter;


};
