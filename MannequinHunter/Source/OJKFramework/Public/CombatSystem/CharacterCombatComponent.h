// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatComponent.h"
#include "Equipment/Equipment.h"
#include "CharacterCombatComponent.generated.h"

/**
 * 
 */

class ACharacter;
class AController;


UENUM()
enum class ECombatEquipmentSlot : uint8
{
	E_MainWeapon = 0,
};

__interface IEquipmentItem
{
	inline AEquipment* GetEquipment(int32 intdex);
	inline void SetEquipment(int32 intdex , AEquipment* equipment);
};

struct FEquipmentItem : IEquipmentItem
{
	inline AEquipment* GetEquipment(int32 intdex);
	inline void SetEquipment(int32 intdex, AEquipment* equipment);
	UPROPERTY()
	AEquipment* equipment;
};

struct FEquipmentItems : IEquipmentItem
{

	inline AEquipment* GetEquipment(int32 intdex);
	inline void SetEquipment(int32 intdex, AEquipment* equipment);
	UPROPERTY()
	TArray<AEquipment*> equipments;
};


DECLARE_DELEGATE_RetVal(FVector2D ,FDodgeDirection);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OJKFRAMEWORK_API UCharacterCombatComponent : public UCombatComponent
{
	GENERATED_BODY()
private:
	static const float DODGE_CHARACTER_INTERP_SPEED;
protected:
	enum ECombatAble : int32
	{
		E_None = 0,
		E_AttackAble = 1,
		E_DodgeAble = E_AttackAble << 1,
		E_HitAble = E_AttackAble << 2,


		//기본 상태?
		E_Default = E_AttackAble | E_DodgeAble | E_HitAble,
	};

	enum EDodgeDirectionIndex : int8
	{
		E_Back = 0,
		E_Front,
		E_Left,
		E_Right,
		E_Front_Left,
		E_Front_Right,
		E_Back_Left,
		E_Back_Right,

		Max,
	};

	enum class EDodgeDirection :int8
	{
		E_Back = 1,
		E_Front = 1 << 1,

		E_Left = 1 << 2,
		E_Right = 1 << 3,

		E_F = E_Front,
		E_FL = E_Front | E_Left,
		E_FR = E_Front | E_Right,

		E_L = E_Left,
		E_R = E_Right,

		E_B = E_Back,
		E_BL = E_Back | E_Left,
		E_BR = E_Back | E_Right,

		E_FB = E_Front | E_Back,
		E_LR = E_Left | E_Right,
	};

	enum ETurnDirection
	{
		E_Left_90 = 0,
		E_Left_180,
		E_Right_90,
		E_Right_180,
	};

public:
	UCharacterCombatComponent();

	void AddAttackCount();

	inline bool IsLockOn() { return targetActor != nullptr; }
	inline FDodgeDirection& DodgeDirectionDelegate() { return dodgeDirectionDelegate; }

	inline AEquipment* GetEquipment(ECombatEquipmentSlot slot, int32 index = 0);

	template<typename TEquipmentItems>
	AEquipment* CreateEquipment(TSubclassOf<AEquipment> createEquipment, ECombatEquipmentSlot slot, int32 addIndex = 0);

	inline void SeCombatAbleDefault() { AddCombatAbleFlag(ECombatAble::E_Default); }
protected:
	inline void AddCombatAbleFlag(ECombatAble combatAble);
	inline void SubtractCombatAbleFlag(ECombatAble combatAble);
	inline void AddCombatAbleFlag(int32 combatAble);
	inline void SubtractCombatAbleFlag(int32 combatAble);
	void LockOn();
	void ChangeCombatType(ECharacterCombatontageType animtype, std::function<void()> callBack = nullptr);
	//사용안함
	void Turn(ECharacterCombatontageType animtype, float yaw);
private:
	int32 GetPreviousAttackCount();
public:
	UFUNCTION(BlueprintCallable)
	void Attack(ECharacterCombatontageType animtype);
	UFUNCTION(BlueprintCallable)
	void Dodge(ECharacterCombatontageType animtype);

	UFUNCTION(BlueprintCallable)
	virtual void SetLockOnTarget();

	UFUNCTION(BlueprintCallable)
	inline void SetIsActorRotation(bool b);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;
protected:
	const struct FAnimMontageArray* currentAnimMontage;
	ECharacterCombatontageType currentAnimType;
	int32 attackCount;

	ECombatAble combatAbleFlag;

	TMap<EDodgeDirection, EDodgeDirectionIndex> eightDodgeDirectionIndexMap;
	TMap<EDodgeDirection, EDodgeDirectionIndex> fourDodgeDirectionIndexMap;

	FDodgeDirection dodgeDirectionDelegate;


	TMap<ECombatEquipmentSlot, TSharedPtr<IEquipmentItem>> equipmentItem;
private:
	float lockOnInterpSpeed;
	float lockOnCharacterInterpSpeed;
	bool isActorRotation;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCombatAnimationData> combatAnimationData;

	UPROPERTY()
	TObjectPtr<ACharacter> owner;
	UPROPERTY()
	TObjectPtr<AController> ownerController;
	UPROPERTY()
	TObjectPtr<AActor> targetActor;

};


