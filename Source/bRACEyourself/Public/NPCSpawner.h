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

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	TSubclassOf<ANPC> NPCclass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	TSubclassOf<AActor> TrackClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	USkeletalMesh* meshes[4];

	UPROPERTY(EditDefaultsOnly, Category = "Spawners")
	UClass* blueprints[4];
	

private:


//timers needed, at least 3, in order to order all of it ;]

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnNPCs(ASpline* Path);


};
