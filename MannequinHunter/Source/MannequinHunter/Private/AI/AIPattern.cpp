// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPattern.h"
#include "Subsystem/AIManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"





UAIPattern::~UAIPattern()
{
	pattern = nullptr;
}

void UAIPattern::LoadTableData(UWorld* world)
{
	UGameInstance* gameInstance = world->GetGameInstance();


	if (gameInstance)
	{
		UAIManagerSubsystem* manager = gameInstance->GetSubsystem<UAIManagerSubsystem>();
		const TSharedPtr<FAIPatternTree>* patternData= manager->GetPattern(tableName);
		if (patternData)
			pattern = *patternData;
	}
}