// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "CarInterface.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Columns = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	Columns->SetupAttachment(GetRootComponent());

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());
	Collision->SetCollisionProfileName("Trigger");
	Collision->SetBoxExtent(FVector(1000.f, 32.f, 300.f));

	bAlreadyChecked = false;
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();


	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UCarInterface>()) {
		if (!bAlreadyChecked) {
			bAlreadyChecked = true;
			CheckpointCrossed.Broadcast();	
		}
	}
}

