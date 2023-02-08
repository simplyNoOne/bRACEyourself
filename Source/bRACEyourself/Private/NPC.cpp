// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "NPCController.h"
#include "Spline.h."
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	SetActorScale3D(FVector(1.1f));

	AutoPossessAI = EAutoPossessAI::Spawned;
	AIControllerClass = ANPCController::StaticClass();
	

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::SetNPCPath(ASpline* pathToSet)
{
	 Path = pathToSet; 
	 ANPCController* NPCCont = Cast<ANPCController>(GetController());
	 if (NPCCont) {
		 NPCCont->UpdatePath(Path);
		 float Duration = (Path->SplinePath->GetSplineLength() / GetMovementComponent()->GetMaxSpeed());
		 NPCCont->WalkPath(Duration);
	 }
}
