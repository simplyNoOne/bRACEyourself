// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCSpawner.h"
#include "Spline.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPCSpawner::ANPCSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HalfWidth = 400.f;

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

void ANPCSpawner::Move()
{
	SetActorRotation(FRotator(0.f, 0.f, GetActorRotation().Yaw + FMath::RandRange(-45.f, 45.f) * (UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetVelocity().Length() / 4000.f)));
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetVelocity().Length());
}

void ANPCSpawner::SpawnPath()
{
	RightPath = GetWorld()->SpawnActor<ASpline>(ASpline::StaticClass(), GetActorLocation() + GetActorRightVector() * HalfWidth, FRotator());
	
	LeftPath = GetWorld()->SpawnActor<ASpline>(ASpline::StaticClass(), GetActorLocation() - GetActorRightVector() * HalfWidth, FRotator());
}

void ANPCSpawner::SpawnPathPoint()
{
	RightPath->AddPoint(GetActorLocation() + GetActorRightVector() * HalfWidth);
	LeftPath->AddPoint(GetActorLocation() - GetActorRightVector() * HalfWidth);
}

void ANPCSpawner::SpawnNPC()
{
	float offset = HalfWidth;
	ASpline* path = RightPath;
	int32 randNum = FMath::RandRange(0, 3);

	if (FMath::RandBool()) {
		offset = -offset;
		path = LeftPath;
	}

	
	ANPC* spawnedNPC = GetWorld()->SpawnActor<ANPC>(NPCclass, GetActorLocation() + GetActorRightVector() * offset, FRotator(0.f));
	spawnedNPC->SetNPCPath(path);
	spawnedNPC->GetMesh()->SetSkeletalMeshAsset(meshes[randNum]);
	spawnedNPC->GetMesh()->SetAnimInstanceClass(blueprints[randNum]->StaticClass());

}

