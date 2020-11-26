// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Boom (pulls towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f; // Camera follows main at this distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller

	// Set size for collisions capsule
	GetCapsuleComponent()->SetCapsuleSize(48.f, 105.f);

	// attach the camera to the spring arm component ("CameraBoom")
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// attach camera to the end of the boom and let the boom adjust to match
	// the controller orientation
	FollowCamera->bUsePawnControlRotation = false;
	// Set are turn rates for input
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// We don't want our character to rotate when the controller rotates
	// Let that just control the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// stops execution if PlayerInputComponent is not valid
	check(PlayerInputComponent);

	// bind action mapping for the jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
	
	// Yaw input is inherited from the Pawn Class, so we can use it here
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Now, for the rate
	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpAtRate);
}

void AMain::MoveForward(float value)
{
	// move the camera in the direction the character is facing/inherited controller from pawn
	if ((Controller != nullptr) && (value != 0.0f))
	{
		// Find out which way is forward. We don't want to edit forward (const)
		const FRotator Rotation = Controller->GetControlRotation();
		// we only care about the direction on the horizontal plane (Yaw)
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// This rotation matrix basically accesses the X, Y, and Z directions of an object in local space
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMain::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		// Find out which way right
		const FRotator Rotation = Controller->GetControlRotation();
		// we only care about the direction on the horizontal plane (Yaw)
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		
		// Note: We are getting a unit vector in that direction, BASED OFF A ROTATION
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AMain::TurnAtRate(float Rate)
{
	// take input from key presses, and add input to controller rotation
	// This will calculuate 65 degree rotations/second
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUpAtRate(float Rate)
{
	// take up and down at 65 degrees/second
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}