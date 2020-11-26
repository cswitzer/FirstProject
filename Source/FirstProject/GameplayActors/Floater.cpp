// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a new static mesh component and assign it to pointer "StaticMesh" - This is a template function
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	initialLocation = FVector(0.0f, 0.0f, 0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f, 0.0f, 0.0f);

	InitialDirection = FVector(0.0f, 0.0f, 0.0f);

	bInitializeFloaterLocations = false;
	bShouldFloat = false;

	InitialForce = FVector(20000000.0f, 0.0f, 0.0f);
	InitialTorque = FVector(20000000.0f, 0.0f, 0.0f);

	RunningTime = 0.0f;

	A = 0.0f;
	B = 0.0f;
	C = 0.0f;
	D = 0.0f;
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	float initialX = FMath::FRandRange(-500.f, 500.f);
	float initialY = FMath::FRandRange(-500.f,500.f);
	float initialZ = FMath::FRandRange(0.f, 500.f);

	initialLocation.X = initialX;
	initialLocation.Y = initialY;
	initialLocation.Z = initialZ;

	PlacedLocation = GetActorLocation();

	// create a vector to set Floater start position
	if (bInitializeFloaterLocations)
	{
		SetActorLocation(initialLocation);
	}

	StaticMesh->AddForce(InitialForce);
	StaticMesh->AddTorqueInRadians(InitialTorque);

	BaseZLocation = PlacedLocation.Z;
	BaseXLocation = PlacedLocation.X;
	BaseYLocation = PlacedLocation.Y;
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	// amount of time since the last frame
	Super::Tick(DeltaTime);

	if (bShouldFloat)
	{
		FVector NewLocation = GetActorLocation();

		NewLocation.Z = BaseZLocation + A * FMath::Sin(B * RunningTime -C) + D; 
		// NewLocation.Y = BaseYLocation + (100.f) * FMath::Sin(RunningTime);
		// NewLocation.X = BaseXLocation + (100.f) * FMath::Cos(RunningTime);

		// Set the location
		SetActorLocation(NewLocation);
		// Every time we tick, increase RunningTime by the change in time
		RunningTime += DeltaTime;
	}
}

/*
AddActorLocalOffset
AddActorLocalRotation
AddForce()
AddTorqueInRadians() or AddTorqueInDegrees
*/
