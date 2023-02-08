// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCSpawner.generated.h"

class ASpline;
class ANPC;

UCLASS()
class BRACEYOURSELF_API ANPCSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCSpawner();

	ASpline* LeftPath;
	ASpline* RightPath;

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	float HalfWidth;

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	TSubclassOf<ANPC> NPCclass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	USkeletalMesh* meshes[4];

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	UAnimBlueprint* blueprints[4];


//timers needed, at least 3, in order to order all of it ;]

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();

	void SpawnPath();
	void SpawnPathPoint();
	void SpawnNPC();

};
