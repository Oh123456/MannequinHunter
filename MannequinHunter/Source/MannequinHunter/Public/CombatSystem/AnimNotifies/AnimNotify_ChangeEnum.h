// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Defines.h"
#include "AnimNotify_ChangeEnum.generated.h"

class UAnimNotifyFunctionObject;
/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API UAnimNotify_ChangeEnum : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FORCEINLINE int64 GetEnumValue();
public:
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
private:
	UPROPERTY(EditAnywhere, meta = (ALLOW_PRIVATE_ACCESS))
	TObjectPtr<UEnum> enumValue;
	UPROPERTY(EditAnywhere, meta = (ALLOW_PRIVATE_ACCESS))
	FName enumClassName;

	UPROPERTY(EditAnywhere, meta = (ALLOW_PRIVATE_ACCESS))
	FName enumValueName;

	UPROPERTY(EditAnywhere, meta = (ALLOW_PRIVATE_ACCESS))
	TSubclassOf<UAnimNotifyFunctionObject> functionObject;
};


FORCEINLINE int64 UAnimNotify_ChangeEnum::GetEnumValue()
{
	if (enumValue == nullptr)
		return -1;

	if (enumValueName.IsNone())
		return -1;
	return enumValue->GetValueByName(enumValueName);
}
