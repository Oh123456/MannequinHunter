// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/BaseAIController.h"
#include "AI/AIPattern.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseActionCharacter.h"
#include "CombatSystem/CharacterCombatComponent.h"
#include "Subsystem/TableSubsystem.h"
#include "Table/ActionDataTable.h"


const FName ABaseAIController::STATE_ENUM = TEXT("StateEnum");
const FName ABaseAIController::CHASE_ENUM_KEY = TEXT("ChaseEnum");
const FName ABaseAIController::TARGET_ACTOR_KEY = TEXT("TargetActor");
const FName ABaseAIController::INITIAL_LOCATION = TEXT("InitialLocation");
const FName ABaseAIController::DEATH = TEXT("IsDeath");

ABaseAIController::ABaseAIController()
{
	aiPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

const UAIPattern* ABaseAIController::GetAIPattern() const
{
	 return AIPattern.GetDefaultObject(); 
}

void ABaseAIController::SetActionTableData(const FName& actionName)
{
	tableData = actionTable->FindRow<FActionTable>(actionName, TEXT(""));
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	if (AIPattern)
	{
		AIPattern.GetDefaultObject()->LoadTableData(GetWorld());
	}

	RunBehaviorTree(behaviorTree);

	ABaseActionCharacter* character = Cast<ABaseActionCharacter>(InPawn);
	if (character)
	{
		character->GetCombatComponent()->OnDeath().AddLambda([this](const FDeathInfo& info)
			{
				Blackboard->SetValueAsBool(DEATH, true);
			});
	}
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	
	UTableSubsystem* tableSubsystem = GetGameInstance()->GetSubsystem<UTableSubsystem>();

	actionTable = tableSubsystem->GetTable<FActionTable>();

	aiPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::TargetPerceptionUpdated);
}

void ABaseAIController::LookTarget(AActor* actor, FAIStimulus stimulus)
{
}

void ABaseAIController::LostTarget(AActor* actor, FAIStimulus stimulus)
{
}

void ABaseAIController::TargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus)
{
	for (const FName& tag : actor->Tags)
	{
		if (targetTags.Contains(tag))
		{
			if (stimulus.WasSuccessfullySensed())
				LookTarget(actor, stimulus);
			else
				LostTarget(actor, stimulus);
			return;
		}
	}

}
