// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/UpDoor.h"
#include "Components/BoxComponent.h"

void AUpDoor::BeginPlay()
{
	Super::BeginPlay();



	trigger->OnComponentBeginOverlap.AddDynamic(this, &AUpDoor::OnOverlapBegin);
	//trigger->OnComponentEndOverlap.AddDynamic(this, &AUpDoor::OnOverlapEnd);

}

void AUpDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	doorMesh->SetRelativeLocation(FVector(0.0f,0.0f,700.0f));
}

void AUpDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	doorMesh->SetRelativeLocation(FVector(0.0f,0.0f,0.0f));
}
