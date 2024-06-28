#pragma once
#include "CombatSystem/MannequinHunterStatus.h"

UENUM(BlueprintType)
enum class EItemType
{
	E_Etc = 0,
	E_Equipment,
	E_Weapon,
};

enum class EWeaponType : uint8;

struct FItemData
{
public:
	FItemData(const FName& itemID, const struct FItemTable* tableData);
	FItemData() : id() , type(){};

	~FItemData() {}

	virtual const FMannequinHunterStatusData GetStatusData() const { return FMannequinHunterStatusData::NoneData; }

public:
	FName id;
	EItemType type;
};

struct FEquipmentItemData : public FItemData
{
public:
	FEquipmentItemData(const FName& itemID, const struct FItemTable* tableData);
	FEquipmentItemData() : FItemData(), statusData(){};

	virtual ~FEquipmentItemData() {}

	virtual const FMannequinHunterStatusData GetStatusData() const override { return statusData; }

	
protected:
	FMannequinHunterStatusData statusData;

};


struct FWeaponItemData : public FEquipmentItemData
{

public:
	FWeaponItemData(const FName& itemID, const struct FItemTable* tableData);
	FWeaponItemData() : FEquipmentItemData() {};

	virtual ~FWeaponItemData() {}

	virtual const FMannequinHunterStatusData GetStatusData() const
	{
		FMannequinHunterStatusData data = statusData;
		data.attack = FMath::RoundToInt(StaticCast<float>(data.attack) * weaponConstant);
		return data;
	}
	float GetWeaponConstant() const { return weaponConstant; }
	EWeaponType GetWeaponType() const { return weaponType; }
	const TSubclassOf<class AEquipment>& GetWeaponClass() const { return weaponClass; }
private:
	float weaponConstant;
	EWeaponType weaponType;
	UPROPERTY()
	TSubclassOf<class AEquipment> weaponClass;
};

static class FItemFactory
{
public:
	static TSharedPtr<FItemData> CreateItemData(const FName& itemID, class UTableSubsystem* tableSubsystem);
};