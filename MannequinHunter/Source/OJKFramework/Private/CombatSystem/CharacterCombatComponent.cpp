// Fill out your copyright notice in the Description page of Project Settings.

#include "OJKFramework.h"
#include "CombatSystem/CharacterCombatComponent.inl"
#include "CombatSystem/CharacterCombatComponent.h"
#include "CombatSystem/CombatAnimationData.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "DebugLog.h"

const float UCharacterCombatComponent::DODGE_CHARACTER_INTERP_SPEED = 7.0f;

UCharacterCombatComponent::UCharacterCombatComponent() : Super(),
attackCount(0) , currentAnimType(ECharacterCombatontageType::E_None) , combatAbleFlag(ECombatAble::E_Default) , 
eightDodgeDirectionIndexMap(), fourDodgeDirectionIndexMap() , targetActor(nullptr), ownerController(nullptr),
owner(nullptr) , lockOnCharacterInterpSpeed(9.0f), lockOnInterpSpeed(7.0f), isActorRotation(true)
{
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_F, EDodgeDirectionIndex::E_Front);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_FL, EDodgeDirectionIndex::E_Front_Left);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_FR, EDodgeDirectionIndex::E_Front_Right);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_L, EDodgeDirectionIndex::E_Left);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_R, EDodgeDirectionIndex::E_Right);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_B, EDodgeDirectionIndex::E_Back);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_BL, EDodgeDirectionIndex::E_Back_Left);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::E_BR, EDodgeDirectionIndex::E_Back_Right);

	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_F, EDodgeDirectionIndex::E_Front);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_FL, EDodgeDirectionIndex::E_Front);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_FR, EDodgeDirectionIndex::E_Front);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_L, EDodgeDirectionIndex::E_Left);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_R, EDodgeDirectionIndex::E_Right);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_B, EDodgeDirectionIndex::E_Back);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_BL, EDodgeDirectionIndex::E_Back);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::E_BR, EDodgeDirectionIndex::E_Back);

	PrimaryComponentTick.bCanEverTick = true;
}


void UCharacterCombatComponent::AddAttackCount()
{
	int32 attackMontageNum = currentAnimMontage->montages.Num();
	attackCount++;
	if (attackMontageNum <= attackCount)
		attackCount = 0;

	//юс╫ц
	AddCombatAbleFlag(ECombatAble::E_Default);
}


void UCharacterCombatComponent::Attack(ECharacterCombatontageType animtype)
{

	ChangeCombatType(animtype, [this]() ->
		void
		{
			this->attackCount = 0;
		});

	if (currentAnimMontage == nullptr)
		return;

	if (combatAbleFlag & ECombatAble::E_AttackAble)
	{
		UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();
		UAnimMontage* attackMontage = currentAnimMontage->montages[attackCount];


		FAnimMontageInstance* animMontageInstance = animInstance->GetActiveInstanceForMontage(currentAnimMontage->montages[GetPreviousAttackCount()]);
		if (animMontageInstance && animMontageInstance->OnMontageEnded.IsBound())
		{
			animMontageInstance->OnMontageEnded.Unbind();
		}

		animInstance->Montage_Play(attackMontage);
		FOnMontageEnded montageEnded;
		montageEnded.BindLambda([this](UAnimMontage* animMontage, bool bInterrupted)
			{
				this->attackCount = 0;
				if (!bInterrupted)
					this->AddCombatAbleFlag(ECombatAble::E_Default);
			});
		animInstance->Montage_SetEndDelegate(montageEnded, attackMontage);
		SubtractCombatAbleFlag((ECombatAble::E_AttackAble | ECombatAble::E_DodgeAble));
	}
}

void UCharacterCombatComponent::Dodge(ECharacterCombatontageType animtype)
{
	ChangeCombatType(animtype);

	if (currentAnimMontage == nullptr)
		return;

	if (combatAbleFlag & ECombatAble::E_DodgeAble)
	{

		bool is8Direction = currentAnimMontage->montages.Num() > 4;

		FVector2D directionVector = UKismetMathLibrary::Normal2D(dodgeDirectionDelegate.Execute());
		UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();
		UAnimMontage* dodgeMontage = nullptr;

		int8 dodgeDirection = 0;

		if (directionVector.Y > 0.f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::E_F);		
		else if (directionVector.Y < 0.f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::E_B);

		if (directionVector.X > 0.0f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::E_R);
		else if (directionVector.X < 0.0f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::E_L);

		EDodgeDirection eDodgeDirection = static_cast<EDodgeDirection>(dodgeDirection);

	
		std::function<void()> IsLockOnCallBack = nullptr;

		if (IsLockOn())
		{
			SetIsActorRotation(false);
			IsLockOnCallBack = [this]()
				{
					SetIsActorRotation(true);
					this->lockOnCharacterInterpSpeed = 9.0f;
				};
		}
		int8 index = 0;
		if (is8Direction)
		{
			index = eightDodgeDirectionIndexMap.FindRef(eDodgeDirection);
		}
		else
		{
			
			int8 LR = static_cast<int8>(EDodgeDirection::E_LR);
			if (dodgeDirection & static_cast<int8>(EDodgeDirection::E_FB) && 
				dodgeDirection & LR)
			{
				FRotator ownerRotator = owner->GetActorRotation();
				FRotator rotator = ownerRotator;
				float yaw = dodgeDirection & static_cast<int8>(EDodgeDirection::E_F) ? 45.0f : -45.0f;
				if (directionVector.X > 0.0f)
					rotator.Yaw += yaw;
				else if (directionVector.X < 0.0f)
					rotator.Yaw += -yaw;
				dodgeDirection &= ~LR;
				eDodgeDirection = static_cast<EDodgeDirection>(dodgeDirection);

				owner->SetActorRotation(rotator);
				
			}
			index = eightDodgeDirectionIndexMap.FindRef(eDodgeDirection);
		}
		FOnMontageEnded montageEnded;
		dodgeMontage = currentAnimMontage->montages[index];

		animInstance->Montage_Play(dodgeMontage);
		lockOnCharacterInterpSpeed = DODGE_CHARACTER_INTERP_SPEED;
		montageEnded.BindLambda([this, IsLockOnCallBack](UAnimMontage* animMontage, bool bInterrupted)
			{
				this->attackCount = 0;
				if (IsLockOnCallBack)
					IsLockOnCallBack();
				if (!bInterrupted)
					this->AddCombatAbleFlag(ECombatAble::E_Default);
			});
		animInstance->Montage_SetEndDelegate(montageEnded, dodgeMontage);

		SubtractCombatAbleFlag((ECombatAble::E_AttackAble | ECombatAble::E_DodgeAble));


	}
}

void UCharacterCombatComponent::Turn(ECharacterCombatontageType animtype, float yaw)
{
	ChangeCombatType(animtype);

	combatAbleFlag = ECombatAble::E_Default;

	UAnimMontage* montage = nullptr;

	if (yaw < 180.0f)
	{
		if (yaw > 135.0f)
		{
			montage = currentAnimMontage->montages[ETurnDirection::E_Right_180];
		}
		else
		{
			montage = currentAnimMontage->montages[ETurnDirection::E_Right_90];
		}
	}
	else
	{
		if (yaw >  315.0f)
		{
			montage = currentAnimMontage->montages[ETurnDirection::E_Left_180];
		}
		else
		{
			montage = currentAnimMontage->montages[ETurnDirection::E_Left_90];
		}
	}

	UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();

	if (!animInstance->Montage_IsPlaying(nullptr))
	{
		FOnMontageEnded montageEnded;
		montageEnded.BindLambda(
			[this](UAnimMontage* animMontage, bool bInterrupted) 
			{
				this->owner->bUseControllerRotationYaw = true; 
			});
		animInstance->Montage_Play(montage, 2.0f);
		animInstance->Montage_SetEndDelegate(montageEnded, montage);
	}
}

void UCharacterCombatComponent::SetLockOnTarget()
{
	targetActor = nullptr;
	isActorRotation = true;
}


void UCharacterCombatComponent::LockOn()
{
	if (targetActor)
	{
		
		FRotator ownerRotator = ownerController->GetControlRotation();;
		
		FVector ownerLocation = owner->GetActorLocation();

		FRotator lookAtRotator = UKismetMathLibrary::FindLookAtRotation(ownerLocation, targetActor->GetActorLocation());
		FRotator newCamRotator = UKismetMathLibrary::RInterpTo(ownerRotator, lookAtRotator, GetWorld()->GetDeltaSeconds(), lockOnInterpSpeed); 
		newCamRotator.Roll = ownerRotator.Roll;
		
		
		ownerController->SetControlRotation(newCamRotator);
		if (isActorRotation)
		{
			FRotator ownerActorRotator = owner->GetActorRotation();
			FRotator newActorRotator = UKismetMathLibrary::RInterpTo(ownerActorRotator, lookAtRotator, GetWorld()->GetDeltaSeconds(), lockOnCharacterInterpSpeed);
			newActorRotator.Roll = ownerRotator.Roll;
			owner->SetActorRotation(newActorRotator);
		}

		
	}
}

void UCharacterCombatComponent::ChangeCombatType(ECharacterCombatontageType animtype, std::function<void()> callBack)
{
	if (currentAnimType == ECharacterCombatontageType::E_None || currentAnimType != animtype)
	{
		currentAnimType = animtype;
		currentAnimMontage = combatAnimationData->GetMontageArray(animtype);
		if (callBack)
			callBack();

	}

}

int32 UCharacterCombatComponent::GetPreviousAttackCount()
{
	int32 attackMontageNum = currentAnimMontage->montages.Num();
	int32 _attackCount = this->attackCount - 1;
	if (_attackCount < 0)
		_attackCount = attackMontageNum - 1;

	return _attackCount;
}

void UCharacterCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LockOn();
}

void UCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<ACharacter>(GetOwner());
	ownerController = owner->GetController();
}
