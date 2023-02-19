// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCSpawner.h"
#include "Spline.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SplineComponent.h"

// Sets default values
ANPCSpawner::ANPCSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ANPCSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCSpawner::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}



void ANPCSpawner::SpawnNPCs(ASpline* Path)
{
	if (GetWorld()) {
		int32 npcNum = FMath::RandRange(1, 4);
		for (int i = 0; i < npcNum; i++) {

			float LocAlong = FMath::RandRange(0.f, Path->SplinePath->GetSplineLength());
			int32 randNum = FMath::RandRange(0, 3);

			ANPC* spawnedNPC = GetWorld()->SpawnActor<ANPC>(NPCclass, Path->SplinePath->GetWorldLocationAtDistanceAlongSpline(LocAlong), FRotator(0.f));
			if (spawnedNPC) {
				spawnedNPC->GetMesh()->SetSkeletalMeshAsset(meshes[randNum]);
				spawnedNPC->GetMesh()->SetAnimInstanceClass(blueprints[randNum]);
				spawnedNPC->SetNPCPath(Path);
			}
			else {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("NPCFail"));
			}
		}
	}
}


