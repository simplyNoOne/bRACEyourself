// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishLine.generated.h"

class UInstancedStaticMeshComponent;
class UBoxComponent;
class USceneComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishLineCrossed);


UCLASS()
class BRACEYOURSELF_API AFinishLine : public AActor
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties

	AFinishLine();



	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, Category = "Checkpoint")
	UInstancedStaticMeshComponent* Columns;

	UPROPERTY(EditDefaultsOnly, Category = "Checkpoint")
	UBoxComponent* Collision;

	UPROPERTY(BlueprintAssignable, Category = "Checkpoint")
	FFinishLineCrossed FinishLineCrossed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
