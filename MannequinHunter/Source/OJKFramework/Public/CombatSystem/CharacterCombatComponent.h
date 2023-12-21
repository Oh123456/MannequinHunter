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
		None = 0,
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

	struct FCharacterCombatData
	{
	
		int32 attackCount = 0;

		ECombatAble combatAbleFlag = ECombatAble::Default;

	
		TMap<ECombatEquipmentSlot, TSharedPtr<IEquipmentItem>> equipmentItem = {};

		UPROPERTY()
		TObjectPtr<ACharacter> owner = nullptr;
		UPROPERTY()
		TObjectPtr<AController> ownerController = nullptr;


	};

	
	struct FCharacterCombatAnimationData
	{
		//const struct FAnimMontageArray* currentAnimMontage = nullptr;
		UPROPERTY()
		const TArray<UAnimMontage*>* currentAnimMontages = nullptr;
		ECharacterCombatMontageType currentAnimType;

		TMap<EDodgeDirection, EDodgeDirectionIndex> eightDodgeDirectionIndexMap = {};
		TMap<EDodgeDirection, EDodgeDirectionIndex> fourDodgeDirectionIndexMap = {};

		FDodgeDirection dodgeDirectionDelegate = {};
	};

	struct FCharacterCombatRotationData
	{
		float lockOnInterpSpeed = 7.0f;
		float lockOnCharacterInterpSpeed = 9.0f;
		bool isActorRotation = true;

		UPROPERTY()
		TObjectPtr<AActor> targetActor = nullptr;
	};

public:
	UCharacterCombatComponent();

	void AddAttackCount();

	void SetCombatAnimationData(class UBaseCombatAnimationData* animationData) { combatAnimationData = animationData; }

	const class UBaseCombatAnimationData* const GetCombatAnimationData() const { return combatAnimationData; }

	inline bool IsLockOn() { return characterRotationData.targetActor != nullptr; }
	inline FDodgeDirection& DodgeDirectionDelegate() { return characterCombatAnimationData.dodgeDirectionDelegate; }

	inline AEquipment* GetEquipment(ECombatEquipmentSlot slot, int32 index = 0);

	template<typename TEquipmentItems>
	TEquipmentItems* CreateEquipment(TSubclassOf<AEquipment> createEquipment, ECombatEquipmentSlot slot, int32 addIndex = 0);

	AEquipment* CreateEquipment(TSubclassOf<AEquipment> createEquipment, ECombatEquipmentSlot slot, int32 addIndex = 0);

	inline void SetCombatAbleDefault() { AddCombatAbleFlag(ECombatAble::Default); }

	inline int32 GetAttackCount() { return characterCombatData.attackCount; }
	void ResetAttackCount() { characterCombatData.attackCount = 0; }

	ECharacterCombatMontageType GetCurrentCombatMontageType() const { return characterCombatAnimationData.currentAnimType; }
	
	void ResetLockOn();
protected:
	inline void AddCombatAbleFlag(ECombatAble combatAble);
	inline void SubtractCombatAbleFlag(ECombatAble combatAble);
	inline void AddCombatAbleFlag(int32 combatAble);
	inline void SubtractCombatAbleFlag(int32 combatAble);
	void LockOn();
	void ChangeCombatType(ECharacterCombatMontageType animtype, std::function<void()> callBack = nullptr);
	//사용안함
	void Turn(ECharacterCombatMontageType animtype, float yaw);


	void SetTargetActor(AActor* target) { characterRotationData.targetActor = target; }
	const AActor* GetTargetActor() const { return characterRotationData.targetActor; }

private:
	int32 GetPreviousAttackCount();
	int8 DodgeDirection(const FVector2D& directionVector);
public:
	// Not Use HFSM !!
	// if UserCharacter Use HFSM ,
	// Use other functions of the same name
	UFUNCTION(BlueprintCallable)
	void Attack(ECharacterCombatMontageType animtype);
	// Not Use HFSM !!
	// if UserCharacter Use HFSM ,
	// Use other functions of the same name
	UFUNCTION(BlueprintCallable)
	void Dodge(ECharacterCombatMontageType animtype);

	UFUNCTION(BlueprintCallable)
	virtual void SetLockOnTarget();

	UFUNCTION(BlueprintCallable)
	inline void SetIsActorRotation(bool b);

public:
	virtual void Dodge(ECharacterCombatMontageType animtype, std::function<void()> endcallback, std::function<void()> cancelCallback = nullptr);
	virtual void Attack(ECharacterCombatMontageType animtype, std::function<void()> endcallback, std::function<void()> cancelCallback = nullptr);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;
protected:
	FCharacterCombatData characterCombatData;
	FCharacterCombatAnimationData characterCombatAnimationData;
private:
	FCharacterCombatRotationData characterRotationData;
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBaseCombatAnimationData> combatAnimationData;



};
