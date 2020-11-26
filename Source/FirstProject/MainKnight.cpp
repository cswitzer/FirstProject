// Fill out your copyright notice in the Description page of Project Settings.


#include "MainKnight.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainKnight::AMainKnight()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the spring arm to the root component, or our character
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f; // Camera follows main at this distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// attaching the camera to the end of the boom. The boom controls camera's rotaion
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Set size for collisions capsule
	GetCapsuleComponent()->SetCapsuleSize(48.f, 105.f);

	// set turning rates
	BaseLookUpRate = 65.0f;
	BaseTurnRate = 65.0f;

	// the character will not rotate when the controller rotates. That will only affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// the direction of rotation is typically the direction the camera is facing
	GetCharacterMovement()->bOrientRotationToMovement = true; // character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void AMainKnight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// check if the player input component is valid
	check(PlayerInputComponent);

	// bind action mapping for the jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainKnight::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainKnight::MoveRight);

	// Yaw input is inherited from the Pawn Class, so we can use it here
	// This is for the mouse input!
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Now, for the rate
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainKnight::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainKnight::LookUpAtRate);

}

void AMainKnight::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0))
	{
		// get orientation direction of controller
		const FRotator Rotation = Controller->GetControlRotation();
		// we only care about the yaw input
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// get a unit vector in the direction of 'YawRotation'
		// our value will multiply by this value to initiate character movement
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMainKnight::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0))
	{
		// get orientation direction of controller
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AMainKnight::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainKnight::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}