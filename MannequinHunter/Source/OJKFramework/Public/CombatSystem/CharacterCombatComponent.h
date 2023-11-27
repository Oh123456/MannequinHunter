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
		None = 0,
		AttackAble = 1,
		DodgeAble = AttackAble << 1,
		HitAble = AttackAble << 2,


		//기본 상태?
		Default = AttackAble | DodgeAble | HitAble,
	};

	enum EDodgeDirectionIndex : int8
	{
		Back = 0,
		Front,
		Left,
		Right,
		Front_Left,
		Front_Right,
		Back_Left,
		Back_Right,

		Max,
	};

	enum class EDodgeDirection :int8
	{
		Back = 1,
		Front = 1 << 1,

		Left = 1 << 2,
		Right = 1 << 3,

		F = Front,
		FL = Front | Left,
		FR = Front | Right,

		L = Left,
		R = Right,

		B = Back,
		BL = Back | Left,
		BR = Back | Right,

		FB = Front | Back,
		LR = Left | Right,
	};

	enum ETurnDirection
	{
		Left_90 = 0,
		Left_180,
		Right_90,
		Right_180,
	};

public:
	UCharacterCombatComponent();

	void AddAttackCount();

	void SetCombatAnimationData(class UCombatAnimationData* animationData) { combatAnimationData = animationData; }

	inline bool IsLockOn() { return targetActor != nullptr; }
	inline FDodgeDirection& DodgeDirectionDelegate() { return dodgeDirectionDelegate; }

	inline AEquipment* GetEquipment(ECombatEquipmentSlot slot, int32 index = 0);

	template<typename TEquipmentItems>
	AEquipment* CreateEquipment(TSubclassOf<AEquipment> createEquipment, ECombatEquipmentSlot slot, int32 addIndex = 0);

	inline void SeCombatAbleDefault() { AddCombatAbleFlag(ECombatAble::Default); }

	inline int32 GetAttackCount() { return attackCount; }
	void ResetAttackCount() { attackCount = 0; }

	void Dodge(ECharacterCombatontageType animtype, std::function<void()> endcallback, std::function<void()> cancelCallback = nullptr);
	void Attack(ECharacterCombatontageType animtype, std::function<void()> endcallback, std::function<void()> cancelCallback = nullptr);

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
	// Not Use HFSM !!
	// if UserCharacter Use HFSM ,
	// Use other functions of the same name
	UFUNCTION(BlueprintCallable)
	void Attack(ECharacterCombatontageType animtype);
	// Not Use HFSM !!
	// if UserCharacter Use HFSM ,
	// Use other functions of the same name
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


