// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLine.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CarInterface.h"

// Sets default values
AFinishLine::AFinishLine()
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
	Collision->SetBoxExtent(FVector(1200.f, 32.f, 400.f));

	bCrossed = false;
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bCrossed) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("lkahsikjsh"));
		if (OtherActor->Implements<UCarInterface>()) {
			bCrossed = true;
			FinishLineCrossed.Broadcast();
		}
	}
}

