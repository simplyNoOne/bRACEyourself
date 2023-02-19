// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CarMovementComponent.h"
#include "CustomPlayerController.h"



ACar::ACar()
{
	
	GetVehicleMovementComponent()->DestroyComponent();
	MovementComponent = CreateDefaultSubobject<UCarMovementComponent>(TEXT("MovementComponent"));
	GetMesh()->SetSimulatePhysics(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 650.f;
	SpringArm->TargetOffset = FVector(0.f, 0.f, 150.f);
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->CameraLagMaxDistance = 250.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(0.f, -10.f, 0.f));


	MaxEnergy = 100.f;
	Energy = MaxEnergy;
	Distance = 0.f;

}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",MovementComponent, &UCarMovementComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACar::SetSteering);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("GearUp", IE_Pressed, MovementComponent, &UCarMovementComponent::GearUp);
	PlayerInputComponent->BindAction("GearDown", IE_Pressed, MovementComponent, &UCarMovementComponent::GearDown);
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &ACar::SetHandbrakeOn);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &ACar::SetHandbrakeOff);
	
}


void ACar::UpdateDistance(float dT)
{
	Distance += (MovementComponent->GetForwardSpeed()* dT)/100;
}

void ACar::UpdateEnergy(float dT)
{
	if(Energy > 0.f)
		Energy -=( MovementComponent->GetEnergyConsumption() * dT);
	else {
		Energy = 0.f;
		MovementComponent->EngineState = EEngineState::EES_Off;
		MovementComponent->SetThrottleInput( 0);
	}
	
}

void ACar::StartCar()
{
	MovementComponent->SetTargetGear(0, true);
	MovementComponent->EngineState = EEngineState::EES_Forward;
}

void ACar::SetThrottle_Implementation(float value)
{
	Throttle = value;
}

void ACar::SetHandbrakeOn()
{
	Handbrake = true;
	MovementComponent->SetHandbrakeInput(true);
}

void ACar::SetHandbrakeOff()
{
	Handbrake = false;
	MovementComponent->SetHandbrakeInput(false);
}

void ACar::SetSteering(float value)
{
	Steering = value;
	MovementComponent->SetSteeringInput(value);
}

EEngineState ACar::GetEngineState()
{
	 return MovementComponent->EngineState; 
}

float ACar::GetMaxRPM()
{
	return MovementComponent->GetEngineMaxRotationSpeed();
}

float ACar::GetCarRPM()
{
	return MovementComponent->GetEngineRotationSpeed();
}

int32 ACar::GetCarGear()
{
	return MovementComponent->GetTargetGear();
}

float ACar::GetDistance()
{
	 return Distance; 
}

float ACar::GetEnergyRatio()
{
	return Energy / MaxEnergy;
}

float ACar::GetCarSpeed()
{
	return (MovementComponent->GetForwardSpeed() * 0.036);
}

void ACar::NPChit_Implementation() {
	Energy += 10.f;
	if (Energy > MaxEnergy)
		Energy = MaxEnergy;
	EnergyBoosted.Broadcast();
}
