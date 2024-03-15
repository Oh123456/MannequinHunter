// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_TargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Controller/BaseAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTS_TargetLocation::UBTS_TargetLocation()
{
	bCreateNodeInstance = true;
}

void UBTS_TargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* bbc = OwnerComp.GetBlackboardComponent();

	AActor* targetActor = Cast<AActor>(bbc->GetValueAsObject(GetSelectedBlackboardKey()));
	ACharacter* character = Cast<ACharacter>(Cast<AAIController>(OwnerComp.GetOwner())->GetPawn());
	FVector ownerPawnLocation = character->GetActorLocation();
	if (targetActor)
	{
		//FVector2D::Normalize
		FVector normal = (targetActor->GetActorLocation() - ownerPawnLocation).GetSafeNormal();

		FVector moveLocationVector = (normal * (character->GetCharacterMovement()->GetMaxSpeed() * DeltaSeconds)) + ownerPawnLocation;

		bbc->SetValueAsVector(moveLocation.SelectedKeyName, moveLocationVector);
	}
}
