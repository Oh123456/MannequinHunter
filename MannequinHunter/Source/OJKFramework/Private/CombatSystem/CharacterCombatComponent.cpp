// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatSystem/CharacterCombatComponent.h"
#include "CombatSystem/CharacterCombatComponent.inl"
#include "CombatSystem/CombatAnimationData.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "OJKFramework.h"
#include "TimerManager.h"
#include "DebugLog.h"

const float UCharacterCombatComponent::DODGE_CHARACTER_INTERP_SPEED = 7.0f;

UCharacterCombatComponent::UCharacterCombatComponent() : Super(),
attackCount(0) , currentAnimType(ECharacterCombatontageType::None) , combatAbleFlag(ECombatAble::Default) , 
eightDodgeDirectionIndexMap(), fourDodgeDirectionIndexMap() , targetActor(nullptr), ownerController(nullptr),
owner(nullptr) , lockOnCharacterInterpSpeed(9.0f), lockOnInterpSpeed(7.0f), isActorRotation(true)
{
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::F, EDodgeDirectionIndex::Front);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::FL, EDodgeDirectionIndex::Front_Left);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::FR, EDodgeDirectionIndex::Front_Right);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::L, EDodgeDirectionIndex::Left);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::R, EDodgeDirectionIndex::Right);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::B, EDodgeDirectionIndex::Back);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::BL, EDodgeDirectionIndex::Back_Left);
	eightDodgeDirectionIndexMap.Add(EDodgeDirection::BR, EDodgeDirectionIndex::Back_Right);

	fourDodgeDirectionIndexMap.Add(EDodgeDirection::F, EDodgeDirectionIndex::Front);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::FL, EDodgeDirectionIndex::Front);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::FR, EDodgeDirectionIndex::Front);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::L, EDodgeDirectionIndex::Left);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::R, EDodgeDirectionIndex::Right);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::B, EDodgeDirectionIndex::Back);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::BL, EDodgeDirectionIndex::Back);
	fourDodgeDirectionIndexMap.Add(EDodgeDirection::BR, EDodgeDirectionIndex::Back);

	PrimaryComponentTick.bCanEverTick = true;
}


void UCharacterCombatComponent::AddAttackCount()
{
	int32 attackMontageNum = currentAnimMontage->montages.Num();
	attackCount++;
	if (attackMontageNum <= attackCount)
		attackCount = 0;

	//юс╫ц
	AddCombatAbleFlag(ECombatAble::Default);
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

	if (combatAbleFlag & ECombatAble::AttackAble)
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
					this->AddCombatAbleFlag(ECombatAble::Default);
			});
		animInstance->Montage_SetEndDelegate(montageEnded, attackMontage);
		SubtractCombatAbleFlag((ECombatAble::AttackAble | ECombatAble::DodgeAble));
	}
}
void UCharacterCombatComponent::Dodge(ECharacterCombatontageType animtype, std::function<void()> callback, std::function<void()> cancelCallback)
{
	ChangeCombatType(animtype);

	if (currentAnimMontage == nullptr)
		return;

	bool is8Direction = currentAnimMontage->montages.Num() > 4;

	FVector2D directionVector = UKismetMathLibrary::Normal2D(dodgeDirectionDelegate.Execute());
	UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();
	UAnimMontage* dodgeMontage = nullptr;

	int8 dodgeDirection = 0;

	if (directionVector.Y >= 0.f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::F);
	else if (directionVector.Y < 0.f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::B);

	if (directionVector.X > 0.0f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::R);
	else if (directionVector.X < 0.0f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::L);

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

		int8 LR = static_cast<int8>(EDodgeDirection::LR);
		if (dodgeDirection & static_cast<int8>(EDodgeDirection::FB) &&
			dodgeDirection & LR)
		{
			FRotator ownerRotator = owner->GetActorRotation();
			FRotator rotator = ownerRotator;
			float yaw = dodgeDirection & static_cast<int8>(EDodgeDirection::F) ? 45.0f : -45.0f;
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
	montageEnded.BindLambda([this, IsLockOnCallBack, callback, cancelCallback](UAnimMontage* animMontage, bool bInterrupted)
		{
			this->attackCount = 0;
			if (IsLockOnCallBack)
				IsLockOnCallBack();
			if (!bInterrupted)
			{
				if (callback)
					callback();
			}
			else
			{
				if (cancelCallback)
					cancelCallback();
			}
			//if (!bInterrupted)
			//	this->AddCombatAbleFlag(ECombatAble::Default);

		});
	animInstance->Montage_SetEndDelegate(montageEnded, dodgeMontage);
}

void UCharacterCombatComponent::Attack(ECharacterCombatontageType animtype, std::function<void()> callback, std::function<void()> cancelCallback)
{
	ChangeCombatType(animtype, [this]() ->
		void
		{
			this->attackCount = 0;
		});

	if (currentAnimMontage == nullptr)
		return;

	UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();
	UAnimMontage* attackMontage = currentAnimMontage->montages[attackCount];


	FAnimMontageInstance* animMontageInstance = animInstance->GetActiveInstanceForMontage(currentAnimMontage->montages[GetPreviousAttackCount()]);
	if (animMontageInstance && animMontageInstance->OnMontageEnded.IsBound())
	{
		animMontageInstance->OnMontageEnded.Unbind();
	}

	animInstance->Montage_Play(attackMontage);
	FOnMontageEnded montageEnded;
	montageEnded.BindLambda([this, callback, cancelCallback](UAnimMontage* animMontage, bool bInterrupted)
		{
			if (!bInterrupted)
			{
				this->attackCount = 0;
				if (callback)
					callback();
			}
			else
			{
				if (cancelCallback)
					cancelCallback();
			}
			//if (!bInterrupted)
			//	this->AddCombatAbleFlag(ECombatAble::Default);
		});
	animInstance->Montage_SetEndDelegate(montageEnded, attackMontage);
	AddAttackCount();
}

void UCharacterCombatComponent::Dodge(ECharacterCombatontageType animtype)
{
	ChangeCombatType(animtype);

	if (currentAnimMontage == nullptr)
		return;

	if (combatAbleFlag & ECombatAble::DodgeAble)
	{

		bool is8Direction = currentAnimMontage->montages.Num() > 4;

		FVector2D directionVector = UKismetMathLibrary::Normal2D(dodgeDirectionDelegate.Execute());
		UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();
		UAnimMontage* dodgeMontage = nullptr;

		int8 dodgeDirection = 0;

		if (directionVector.Y > 0.f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::F);		
		else if (directionVector.Y < 0.f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::B);

		if (directionVector.X > 0.0f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::R);
		else if (directionVector.X < 0.0f)
			dodgeDirection |= static_cast<int8>(EDodgeDirection::L);

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
			
			int8 LR = static_cast<int8>(EDodgeDirection::LR);
			if (dodgeDirection & static_cast<int8>(EDodgeDirection::FB) && 
				dodgeDirection & LR)
			{
				FRotator ownerRotator = owner->GetActorRotation();
				FRotator rotator = ownerRotator;
				float yaw = dodgeDirection & static_cast<int8>(EDodgeDirection::F) ? 45.0f : -45.0f;
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
					this->AddCombatAbleFlag(ECombatAble::Default);
			});
		animInstance->Montage_SetEndDelegate(montageEnded, dodgeMontage);

		SubtractCombatAbleFlag((ECombatAble::AttackAble | ECombatAble::DodgeAble));


	}
}

void UCharacterCombatComponent::Turn(ECharacterCombatontageType animtype, float yaw)
{
	ChangeCombatType(animtype);

	combatAbleFlag = ECombatAble::Default;

	UAnimMontage* montage = nullptr;

	if (yaw < 180.0f)
	{
		if (yaw > 135.0f)
		{
			montage = currentAnimMontage->montages[ETurnDirection::Right_180];
		}
		else
		{
			montage = currentAnimMontage->montages[ETurnDirection::Right_90];
		}
	}
	else
	{
		if (yaw >  315.0f)
		{
			montage = currentAnimMontage->montages[ETurnDirection::Left_180];
		}
		else
		{
			montage = currentAnimMontage->montages[ETurnDirection::Left_90];
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
	if (currentAnimType == ECharacterCombatontageType::None || currentAnimType != animtype)
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
