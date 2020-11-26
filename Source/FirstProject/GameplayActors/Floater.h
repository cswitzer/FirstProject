// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class FIRSTPROJECT_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

	// Anything that is not a primitive type will be of type pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshComponents")
	UStaticMeshComponent* StaticMesh;

	// Location used by SetActorLocation() when BeginPlay() is called
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector initialLocation;

	// Location of the actor when dragged in from the editor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	bool bShouldFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	bool bInitializeFloaterLocations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector OtherLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector InitialForce;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector InitialTorque;

private:

	float RunningTime;

	float BaseXLocation;
	float BaseYLocation;
	float BaseZLocation;

public:
	// Amplitude
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float A;

	// Period: Period = 2 * PI / ABS(B) - Controls the speed of oscillating movement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float B;

	// Phase Shift: Phase Shift = ( C / B )
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float C;

	// Vertical Shift is D
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float D;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
