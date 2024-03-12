// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FunctionObject.generated.h"

/**
 * 
 */
UCLASS(abstract)
class MANNEQUINHUNTER_API UFunctionObject : public UObject
{
	GENERATED_BODY()
	

public:
	void operator()()
	{
		Execute();
	}

protected:
	virtual void Execute() {};
};
