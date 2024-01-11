// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatSystem/CharacterCombatComponent.h"
#include "CombatSystem/CharacterCombatComponent.inl"
#include "CombatSystem/CombatAnimationData.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Singleton/ObjectPoolManager.h"
#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "OJKFramework.h"
#include "TimerManager.h"
#include "DebugLog.h"

const float UCharacterCombatComponent::DODGE_CHARACTER_INTERP_SPEED = 7.0f;

UCharacterCombatComponent::UCharacterCombatComponent() : Super(),
characterCombatData(), characterRotationData(), characterCombatAnimationData()
{
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::F, EDirectionIndex::Front);
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::FL, EDirectionIndex::Front_Left);
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::FR, EDirectionIndex::Front_Right);
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::L, EDirectionIndex::Left);
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::R, EDirectionIndex::Right);
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::B, EDirectionIndex::Back);
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::BL, EDirectionIndex::Back_Left);
	characterCombatAnimationData.eightDodgeDirectionIndexMap.Add(EDodgeDirection::BR, EDirectionIndex::Back_Right);

	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::F, EDirectionIndex::Front);
	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::FL, EDirectionIndex::Front);
	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::FR, EDirectionIndex::Front);
	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::L, EDirectionIndex::Left);
	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::R, EDirectionIndex::Right);
	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::B, EDirectionIndex::Back);
	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::BL, EDirectionIndex::Back);
	characterCombatAnimationData.fourDodgeDirectionIndexMap.Add(EDodgeDirection::BR, EDirectionIndex::Back);



	PrimaryComponentTick.bCanEverTick = true;
}


void UCharacterCombatComponent::AddAttackCount()
{
	int32 attackMontageNum = characterCombatAnimationData.currentAnimMontages->Num();
	characterCombatData.attackCount++;
	if (attackMontageNum <= characterCombatData.attackCount)
		characterCombatData.attackCount = 0;

	//юс╫ц
	AddCombatAbleFlag(ECombatAble::Default);
}


void UCharacterCombatComponent::Attack(ECharacterCombatMontageType animtype)
{

	ChangeCombatType(animtype, [this]() ->
		void
		{
			this->characterCombatData.attackCount = 0;
		});

	const TArray<UAnimMontage*>* currentAnimMontages = characterCombatAnimationData.currentAnimMontages;

	if (currentAnimMontages == nullptr)
		return;

	if (characterCombatData.combatAbleFlag & ECombatAble::AttackAble)
	{
		UAnimInstance* animInstance = characterCombatData.owner->GetMesh()->GetAnimInstance();
		UAnimMontage* attackMontage = (*currentAnimMontages)[characterCombatData.attackCount];


		FAnimMontageInstance* animMontageInstance = animInstance->GetActiveInstanceForMontage((*currentAnimMontages)[GetPreviousAttackCount()]);
		if (animMontageInstance && animMontageInstance->OnMontageEnded.IsBound())
		{
			animMontageInstance->OnMontageEnded.Unbind();
		}

		animInstance->Montage_Play(attackMontage);
		FOnMontageEnded montageEnded;
		montageEnded.BindLambda([this](UAnimMontage* animMontage, bool bInterrupted)
			{
				this->characterCombatData.attackCount = 0;
				if (!bInterrupted)
					this->AddCombatAbleFlag(ECombatAble::Default);
			});
		animInstance->Montage_SetEndDelegate(montageEnded, attackMontage);
		SubtractCombatAbleFlag((ECombatAble::AttackAble | ECombatAble::DodgeAble));
	}
}

uint8 UCharacterCombatComponent::OnHitDirection_Implementation()
{
	if (damageCauserActor == nullptr)
		return 0;

	AActor* damageActor = damageCauserActor->GetOwner();

	if (damageActor == nullptr)
		damageActor = damageCauserActor;

	AActor* owner = GetOwner();

	FVector2d ownerForwardVector2D(owner->GetActorForwardVector());

	FVector2d xVector(1.0f, 0.f);

	float degrees = FMath::RadiansToDegrees(FMath::Acos(xVector.Dot(ownerForwardVector2D)));


	FVector2d forwardVector2D(damageActor->GetActorForwardVector());
	FVector2d rotatedVector = forwardVector2D.GetRotated(degrees);
	
	float rotatedVectorAngle = FMath::RadiansToDegrees(FMath::Atan2(rotatedVector.Y, rotatedVector.X));

	uint8 direction = (StaticCast<uint8>((rotatedVectorAngle / 45.0f)) % 8);

	return direction;
}

uint8 UCharacterCombatComponent::ConvertDirectionToHitDirection(uint8 direction)
{
	EDirection eDirection = StaticCast<EDirection>(direction);
	switch (eDirection)
	{
	case UCharacterCombatComponent::EDirection::Front_Right:
	case UCharacterCombatComponent::EDirection::Front_Left:
	case UCharacterCombatComponent::EDirection::Front:
		return StaticCast<uint8>(EHitDirection::Back);

	case UCharacterCombatComponent::EDirection::Right:
		return StaticCast<uint8>(EHitDirection::Left);

	case UCharacterCombatComponent::EDirection::Left:
		return StaticCast<uint8>(EHitDirection::Right);

	case UCharacterCombatComponent::EDirection::Back:
		return StaticCast<uint8>(EHitDirection::Front);

	case UCharacterCombatComponent::EDirection::Back_Left:
		return StaticCast<uint8>(EHitDirection::Front_Right);

	case UCharacterCombatComponent::EDirection::Back_Right:
		return StaticCast<uint8>(EHitDirection::Front_Left);

	default:
		return StaticCast<uint8>(EHitDirection::Back);
	}
}

void UCharacterCombatComponent::Dodge(ECharacterCombatMontageType animtype, float playRate, std::function<void()> callback, std::function<void()> cancelCallback)
{
	ChangeCombatType(animtype);

	const TArray<UAnimMontage*>* currentAnimMontages = characterCombatAnimationData.currentAnimMontages;

	if (currentAnimMontages == nullptr)
		return;

	bool is8Direction = currentAnimMontages->Num() > 4;

	ACharacter* owner = characterCombatData.owner;

	FVector2D directionVector = UKismetMathLibrary::Normal2D(characterCombatAnimationData.dodgeDirectionDelegate.Execute());
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

	const TMap<EDodgeDirection, EDirectionIndex>& eightDodgeDirectionIndexMap = characterCombatAnimationData.eightDodgeDirectionIndexMap;
	std::function<void()> IsLockOnCallBack = nullptr;

	if (IsLockOn())
	{
		SetIsActorRotation(false);
		IsLockOnCallBack = [this]()
			{
				SetIsActorRotation(true);
				this->characterRotationData.lockOnCharacterInterpSpeed = 9.0f;
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
	dodgeMontage = (*currentAnimMontages)[index];

	animInstance->Montage_Play(dodgeMontage, playRate);
	characterRotationData.lockOnCharacterInterpSpeed = DODGE_CHARACTER_INTERP_SPEED;
	montageEnded.BindLambda([this, IsLockOnCallBack, callback, cancelCallback](UAnimMontage* animMontage, bool bInterrupted)
		{
			this->characterCombatData.attackCount = 0;
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

		});
	animInstance->Montage_SetEndDelegate(montageEnded, dodgeMontage);
}

void UCharacterCombatComponent::Attack(ECharacterCombatMontageType animtype, float playRate ,std::function<void()> callback, std::function<void()> cancelCallback)
{
	ChangeCombatType(animtype /*[this]() ->
		void
		{
			this->characterCombatData.attackCount = 0;
		}*/);

	const TArray<UAnimMontage*>* currentAnimMontages = characterCombatAnimationData.currentAnimMontages;

	if (currentAnimMontages == nullptr)
		return;

	ACharacter* owner = characterCombatData.owner;

	UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();
	UAnimMontage* attackMontage = (*currentAnimMontages)[characterCombatData.attackCount];


	FAnimMontageInstance* animMontageInstance = animInstance->GetActiveInstanceForMontage((*currentAnimMontages)[GetPreviousAttackCount()]);
	if (animMontageInstance && animMontageInstance->OnMontageEnded.IsBound())
	{
		animMontageInstance->OnMontageEnded.Unbind();
	}

	animInstance->Montage_Play(attackMontage, playRate);
	characterRotationData.isActorRotation = true;

	if (!IsLockOn())
	{
		FVector2D direction = characterCombatAnimationData.dodgeDirectionDelegate.Execute();
		if (!direction.Equals(FVector2D::Zero()))
		{
			APlayerCharacter* player = Cast<APlayerCharacter>(owner);
			if (player)
			{
				FVector2D yVector(0.0f, 1.0f);
				double degrees = FMath::RadiansToDegrees(FMath::Atan2(direction.X, direction.Y));
				FRotator rotator = owner->GetActorRotation();
				rotator.Yaw = degrees + player->GetController()->GetControlRotation().Yaw;

				owner->SetActorRotation(rotator);

			}
		}
	}
	
	
	FOnMontageEnded montageEnded;
	montageEnded.BindLambda([this, callback, cancelCallback](UAnimMontage* animMontage, bool bInterrupted)
		{
			if (!bInterrupted)
			{
				this->characterCombatData.attackCount = 0;
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

void UCharacterCombatComponent::Dodge(ECharacterCombatMontageType animtype)
{
	ChangeCombatType(animtype);

	const TArray<UAnimMontage*>* currentAnimMontages = characterCombatAnimationData.currentAnimMontages;

	if (currentAnimMontages == nullptr)
		return;

	if (characterCombatData.combatAbleFlag & ECombatAble::DodgeAble)
	{

		bool is8Direction = currentAnimMontages->Num() > 4;

		ACharacter* owner = characterCombatData.owner;
		const TMap<EDodgeDirection, EDirectionIndex>& eightDodgeDirectionIndexMap = characterCombatAnimationData.eightDodgeDirectionIndexMap;

		FVector2D directionVector = UKismetMathLibrary::Normal2D(characterCombatAnimationData.dodgeDirectionDelegate.Execute());
		UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();
		UAnimMontage* dodgeMontage = nullptr;

		int8 dodgeDirection = DodgeDirection(directionVector);
		EDodgeDirection eDodgeDirection = static_cast<EDodgeDirection>(dodgeDirection);
	
		std::function<void()> IsLockOnCallBack = nullptr;

		if (IsLockOn())
		{
			SetIsActorRotation(false);
			IsLockOnCallBack = [this]()
				{
					SetIsActorRotation(true);
					this->characterRotationData.lockOnCharacterInterpSpeed = 9.0f;
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
		dodgeMontage = (*currentAnimMontages)[index];

		animInstance->Montage_Play(dodgeMontage);
		characterRotationData.lockOnCharacterInterpSpeed = DODGE_CHARACTER_INTERP_SPEED;
		montageEnded.BindLambda([this, IsLockOnCallBack](UAnimMontage* animMontage, bool bInterrupted)
			{
				this->characterCombatData.attackCount = 0;
				if (IsLockOnCallBack)
					IsLockOnCallBack();
				if (!bInterrupted)
					this->AddCombatAbleFlag(ECombatAble::Default);
			});
		animInstance->Montage_SetEndDelegate(montageEnded, dodgeMontage);

		SubtractCombatAbleFlag((ECombatAble::AttackAble | ECombatAble::DodgeAble));


	}
}



void UCharacterCombatComponent::Hit(ECharacterCombatMontageType animtype)
{
	ChangeCombatType(animtype);

	characterCombatData.combatAbleFlag = ECombatAble::Default;

	UAnimMontage* montage = nullptr;
	const TArray<UAnimMontage*>* currentAnimMontages = characterCombatAnimationData.currentAnimMontages;
	if (currentAnimMontages == nullptr)
		return;
	ACharacter* owner = characterCombatData.owner;

	UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();

	uint8 direction = ConvertDirectionToHitDirection(OnHitDirection());

	if (currentAnimMontages->Num() <= direction)
		direction = 0;

	montage = (*currentAnimMontages)[direction];

	animInstance->Montage_Play(montage);
}

void UCharacterCombatComponent::Turn(ECharacterCombatMontageType animtype, float yaw)
{
	ChangeCombatType(animtype);

	characterCombatData.combatAbleFlag = ECombatAble::Default;

	UAnimMontage* montage = nullptr;
	const TArray<UAnimMontage*>* currentAnimMontages = characterCombatAnimationData.currentAnimMontages;
	if (currentAnimMontages == nullptr)
		return;
	ACharacter* owner = characterCombatData.owner;
	if (yaw < 180.0f)
	{
		if (yaw > 135.0f)
		{
			montage = (*currentAnimMontages)[ETurnDirection::Right_180];
		}
		else
		{
			montage = (*currentAnimMontages)[ETurnDirection::Right_90];
		}
	}
	else
	{
		if (yaw >  315.0f)
		{
			montage = (*currentAnimMontages)[ETurnDirection::Left_180];
		}
		else
		{
			montage = (*currentAnimMontages)[ETurnDirection::Left_90];
		}
	}

	UAnimInstance* animInstance = owner->GetMesh()->GetAnimInstance();

	if (!animInstance->Montage_IsPlaying(nullptr))
	{
		FOnMontageEnded montageEnded;
		montageEnded.BindLambda(
			[this](UAnimMontage* animMontage, bool bInterrupted) 
			{
				this->characterCombatData.owner->bUseControllerRotationYaw = true;
			});
		animInstance->Montage_Play(montage, 2.0f);
		animInstance->Montage_SetEndDelegate(montageEnded, montage);
	}
}

void UCharacterCombatComponent::SetLockOnTarget()
{
	ResetLockOn();
}

void UCharacterCombatComponent::LockOn()
{
	AActor* targetActor = characterRotationData.targetActor;
	if (targetActor)
	{
		ACharacter* owner = characterCombatData.owner;
		AController* ownerController = characterCombatData.ownerController;

		FRotator ownerRotator = ownerController->GetControlRotation();;
		
		FVector ownerLocation = owner->GetActorLocation();

		FRotator lookAtRotator = UKismetMathLibrary::FindLookAtRotation(ownerLocation, targetActor->GetActorLocation());
		FRotator newCamRotator = UKismetMathLibrary::RInterpTo(ownerRotator, lookAtRotator, GetWorld()->GetDeltaSeconds(), characterRotationData.lockOnInterpSpeed);
		newCamRotator.Roll = ownerRotator.Roll;
		
		
		ownerController->SetControlRotation(newCamRotator);
		if (characterRotationData.isActorRotation)
		{
			FRotator ownerActorRotator = owner->GetActorRotation();
			FRotator newActorRotator = UKismetMathLibrary::RInterpTo(ownerActorRotator, lookAtRotator, GetWorld()->GetDeltaSeconds(), characterRotationData.lockOnCharacterInterpSpeed);
			newActorRotator.Roll = ownerRotator.Roll;
			owner->SetActorRotation(newActorRotator);
		}

		
	}
}

void UCharacterCombatComponent::ResetLockOn()
{
	characterRotationData.targetActor = nullptr;
	characterRotationData.isActorRotation = true;
}

void UCharacterCombatComponent::ChangeCombatType(ECharacterCombatMontageType animtype, std::function<void()> callBack)
{

	if (characterCombatAnimationData.currentAnimType == ECharacterCombatMontageType::None || characterCombatAnimationData.currentAnimType != animtype)
	{
		characterCombatAnimationData.currentAnimType = animtype;
		characterCombatAnimationData.currentAnimMontages = combatAnimationData->GetMontageArray(animtype);
		if (callBack)
			callBack();

	}

}

int32 UCharacterCombatComponent::GetPreviousAttackCount()
{
	int32 attackMontageNum = characterCombatAnimationData.currentAnimMontages->Num();
	int32 _attackCount = this->characterCombatData.attackCount - 1;
	if (_attackCount < 0)
		_attackCount = attackMontageNum - 1;

	return _attackCount;
}

void UCharacterCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LockOn();
}

void UCharacterCombatComponent::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);
	Hit(ECharacterCombatMontageType::Hit1);
}

void UCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	characterCombatData.owner = Cast<ACharacter>(GetOwner());
	characterCombatData.ownerController = characterCombatData.owner->GetController();
}



AEquipment* UCharacterCombatComponent::CreateEquipment(TSubclassOf<AEquipment> createEquipment, ECombatEquipmentSlot slot, int32 addIndex )
{
	TSharedPtr<IEquipmentItem>* findItem = characterCombatData.equipmentItem.Find(slot);

	if (findItem == nullptr)
	{
		TSharedPtr<IEquipmentItem> newObject = MakeShared<FEquipmentItem>();

		findItem = &characterCombatData.equipmentItem.Add(slot, newObject);
	}

	FObjectPoolManager* objectPoolManager = FObjectPoolManager::GetInstance();
	
	AEquipment* createObject = objectPoolManager->GetActor<AEquipment>(createEquipment);
	(*findItem)->SetEquipment(addIndex, createObject);

	return createObject;
}

int8 UCharacterCombatComponent::DodgeDirection(const FVector2D& directionVector)
{
	int8 dodgeDirection;
	if (directionVector.Y > 0.f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::F);
	else if (directionVector.Y < 0.f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::B);

	if (directionVector.X > 0.0f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::R);
	else if (directionVector.X < 0.0f)
		dodgeDirection |= static_cast<int8>(EDodgeDirection::L);

	return dodgeDirection;
}