// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPattern.h"
#include "Subsystem/TableSubsystem.h"
#include "Kismet/GameplayStatics.h"




UAIPattern::~UAIPattern()
{
	tableData = nullptr;
}

void UAIPattern::LoadTableData(UWorld* world)
{
	UGameInstance* gameInstance = world->GetGameInstance();


	if (gameInstance)
	{
		//const UDataTable* table = gameInstance->GetSubsystem<UTableSubsystem>()->GetTable<FAIPatternTreeTable>();
		//const UDataTable* patternDataTable = gameInstance->GetSubsystem<UTableSubsystem>()->GetTable<FAIPatternDataTable>();
		//if (table)
		//{
		//	using AICommandListNode = TCommandListNode<FName, FAICommandTreeData>;
		//	TSharedPtr<AICommandListNode>* node = nullptr;
		//	tableData = table->FindRow<FAIPatternTreeTable>(tableName, TEXT(""));

		//	// ±‚¥… øœ∑· µ«∏È ΩÃ±€≈Ê¿∏∑Œ πŸ≤‹∞Õ
		//	const TMap<int32, FAIPatternTreeTableDataArray>& patternData = tableData->patternData;

		//	for (const auto& pair : patternData)
		//	{
		//		FAICommandTreeData data;

		//		for (const FAIPatternTreeTableData& patternTreeTableData : pair.Value.datas)
		//		{

		//		}

		//	}


		//	AICommandList.ForEach([this](TSharedPtr<TCommandListNode<FName, FAICommandTreeData>>& nodeData)
		//		{
		//			const TSharedPtr<FAICommandTreeData>* node = nodeData->GetValue();

		//			if (node)
		//			{
		//				const TArray<TSharedPtr<TCommandListNode<FName, FAICommandTreeData>>>& childs = nodeData->GetChilds();

		//				int32 total = 0;
		//				for (const TSharedPtr<TCommandListNode<FName, FAICommandTreeData>>& child : childs)
		//				{
		//					const TSharedPtr<FAICommandTreeData>* childNode = child->GetValue();
		//					if (childNode)
		//					{
		//						const int32 weight = (*childNode)->GetWeight();
		//						(*childNode)->AddWeightArray(weight + total);
		//						total += weight;
		//					}
		//				}
		//			}

		//		});
		//}
	}
}

const FAIPatternTreeTableDataArray* UAIPattern::GetAIPatternData(float distance) const
{
	if (tableData == nullptr)
		return nullptr;

	return nullptr;
}

