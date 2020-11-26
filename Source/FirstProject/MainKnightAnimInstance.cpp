// Fill out your copyright notice in the Description page of Project Settings.


#include "MainKnightAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainKnightAnimInstance::NativeInitializeAnimation()
{
	if (pawn == nullptr)
	{
		pawn = TryGetPawnOwner();
	}
}

void UMainKnightAnimInstance::UpdateAnimationProperties()
{
	if (pawn == nullptr)
	{
		pawn = TryGetPawnOwner();
	}

	if (pawn)
	{
		// Get the pawn's speed
		FVector Speed = pawn->GetVelocity();
		// update horizontal/lateral movement
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		// Getting magnitude of hor. velocity. This sets our movement speed, which is a float
		MovementSpeed = LateralSpeed.Size();

		// is the character in the air?
		bIsInAir = pawn->GetMovementComponent()->IsFalling();
	}
}