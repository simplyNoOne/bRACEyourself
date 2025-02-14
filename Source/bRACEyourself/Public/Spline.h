// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spline.generated.h"

class USplineComponent;

UCLASS()
class BRACEYOURSELF_API ASpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpline();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NPCs")
	USplineComponent* SplinePath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NPCs")
	bool bGhostSpline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Blueprintable, Category = "NPCs")
	void AddPoint(FVector Location);
	
	float GetLength();

};
