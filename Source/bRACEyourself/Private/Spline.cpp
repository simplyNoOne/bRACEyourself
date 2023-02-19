// Fill out your copyright notice in the Description page of Project Settings.


#include "Spline.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"
#include "NPCSpawner.h"

// Sets default values
ASpline::ASpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("SplinePath"));

	bGhostSpline = false;
	
}

// Called when the game starts or when spawned
void ASpline::BeginPlay()
{
	Super::BeginPlay();

	if (!bGhostSpline) {
		AActor* Spawner = UGameplayStatics::GetActorOfClass(GetWorld(), ANPCSpawner::StaticClass());
		if (Spawner)
			Cast<ANPCSpawner>(Spawner)->SpawnNPCs(this);
	}
}

// Called every frame
void ASpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpline::AddPoint(FVector Location)
{
	SplinePath->AddSplinePoint(Location, ESplineCoordinateSpace::World, true);
}

float ASpline::GetLength()
{
	return SplinePath->GetSplineLength();
}

