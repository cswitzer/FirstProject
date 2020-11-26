// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// call the parent tick component function
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// the pawn that owns the movement component
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		// If there is no pawn owner, updated component, or we should skip updating, exit the function
		return;
	}

	// how much should we move every frame/return value of input vector, then clear the vector out
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		// the sweep parameter set to true will let us into the if statement below
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
	
		// if we bump into something, glide along the side of it
		if (Hit.IsValidBlockingHit())
		{
			// 1 - Hit.Time is the point in time of the hit
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}