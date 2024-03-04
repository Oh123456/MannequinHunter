// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_Pattern.h"
#include "AI/AIPattern.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/BaseAIController.h"


UBTS_Pattern::UBTS_Pattern()
{
	bCreateNodeInstance = true;
}

void UBTS_Pattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTS_Pattern::SetOwner(AActor* ActorOwner)
{
	ABaseAIController* AIController = ActorOwner->GetInstigatorController<ABaseAIController>();

	if (AIController)
	{
		const UAIPattern* AIPattern = AIController->GetAIPattern();

		int32 defaultWeight = AIPattern->GetDefaultWeight();
		int32 totalWeight = defaultWeight;

		patternDatas.Add(FPatternData(TEXT("None"), defaultWeight));

		//for (const FName& name : patternNames)
		//{
		//	const FAIPatternData* data = AIPattern->GetAIPatternData(name);
		//	if (data->weight <= 0)
		//		continue;
		//	FPatternData patternData;
		//	patternData.nameKey = name;
		//	patternData.weight = data->weight + totalWeight;
		//	totalWeight += data->weight;
		//	patternDatas.Add(patternData);
		//}

		//for (FPatternData& data : patternDatas)
		//{
		//	data.weight /= totalWeight;
		//	//UE_LOG(LogTemp, Log, TEXT("%s Is %f Total %d"), *data.nameKey.ToString(), data.weight , totalWeight);
		//}

	}
}
