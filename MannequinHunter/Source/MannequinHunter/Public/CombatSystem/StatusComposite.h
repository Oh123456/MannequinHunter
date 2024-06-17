#pragma once

#include "MannequinHunterStatus.h"

struct IStatusComposite
{
	virtual void GetStatusData(class UWorld* worldObject,FMannequinHunterStatus& OUT characterStatus) = 0;
};


class FStatusComposite : public IStatusComposite
{
public:
	void AddComposite(const TSharedPtr<IStatusComposite>& composite);

	virtual void GetStatusData(class UWorld* worldObject, FMannequinHunterStatus& OUT characterStatus) override;
private:
	TArray<TSharedPtr<IStatusComposite>> composites;
};

class FEquipmentComposite : public IStatusComposite
{
public:
	virtual void GetStatusData(class UWorld* worldObject, FMannequinHunterStatus& OUT characterStatus) override;
};