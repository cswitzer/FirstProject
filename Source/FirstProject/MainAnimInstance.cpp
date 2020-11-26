// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

// like the begin play function
void UMainAnimInstance::NativeInitializeAnimation()
{
	if (pawn == nullptr)
	{
		// which pawn owns this animation instance?
		pawn = TryGetPawnOwner();
	}
}

// like the 'tick' function
void UMainAnimInstance::UpdateAnimationProperties()
{
	if (pawn == nullptr)
	{
		pawn = TryGetPawnOwner();
	}

	if (pawn)
	{
		// get the pawn's velocity
		FVector Speed = pawn->GetVelocity();
		// update horizontal/lateral movement
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		// Getting magnitude of hor. velocity. This sets our movement speed, which is a float
		MovementSpeed = LateralSpeed.Size();

		// is the character falling?
		bIsInAir = pawn->GetMovementComponent()->IsFalling();
	}
}