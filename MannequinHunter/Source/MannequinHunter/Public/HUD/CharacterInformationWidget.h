// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterInformationWidget.generated.h"

/**
 * 
 */
struct FStatusData;
enum class EEquipment;


UCLASS()
class MANNEQUINHUNTER_API UCharacterInformationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	enum class EChangeInformationData
	{
		E_Nome = 0,
		E_Status = 1,
		E_Equipment = 1 << 1,
	};


private:
	void UpdateStatus(const TSharedPtr<FStatusData>& data);
	void ChangeStatus(const TSharedPtr<FStatusData>& data);
	void UpdateEquipment();
	void ChangeEquipment(EEquipment slot, const TSharedPtr<struct FItemData> data);
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
private:
	UPROPERTY()
	TObjectPtr<class UHorizontalBox> equipmentBox = nullptr;
	UPROPERTY()
	TObjectPtr<class UGridPanel> infoPanel = nullptr;

	//FDelegateHandle changeStatusDelegateHandle;
	//FDelegateHandle changeEquipmentDelegateHandle;

	EChangeInformationData changeData = EChangeInformationData::E_Nome;
};


ENUM_CLASS_FLAGS(UCharacterInformationWidget::EChangeInformationData);