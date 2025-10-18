// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/BotPawn.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABotPawn::ABotPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	RootComponent = PawnMesh;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent);
	
	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void ABotPawn::BeginPlay()
{
	Super::BeginPlay();

	if (IMCBot)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				EnhancedInputSubsystem->AddMappingContext(IMCBot, 0);
			}
		}	
	}
}

FVector ABotPawn::GetDirectionVector(const float& AxisValue, const EMovementDirection& MovementDirection) const
{
	FVector DirectionVectorScaled{ 0.0f };

	if (GetController())
	{
		switch (MovementDirection)
		{
			case EMovementDirection::Right: // if x == 1 or x == -1 // x != 0
				DirectionVectorScaled = UKismetMathLibrary::GetRightVector(GetController()->GetControlRotation()) * AxisValue;
				break;
			case EMovementDirection::Forward: // if y == 1 or y == -1 // y != 0
				DirectionVectorScaled = UKismetMathLibrary::GetForwardVector(GetController()->GetControlRotation()) * AxisValue;
				break;
			case EMovementDirection::Up: // if z != 0
				DirectionVectorScaled = UKismetMathLibrary::GetUpVector(GetController()->GetControlRotation()) * AxisValue;
				break;
		}
	}

	return DirectionVectorScaled;
}

void ABotPawn::HandleFloatingPawnMovement(const FInputActionValue& InputActionValue)
{
	if (FloatingPawnMovementComponent)
	{
		const FVector InputAxisValue = InputActionValue.Get<FVector>();
		if (InputAxisValue.X != 0.0f) FloatingPawnMovementComponent->AddInputVector(GetDirectionVector(InputAxisValue.X, EMovementDirection::Right));
		if (InputAxisValue.Y != 0.0f) FloatingPawnMovementComponent->AddInputVector(GetDirectionVector(InputAxisValue.Y, EMovementDirection::Forward));
		if (InputAxisValue.Z != 0.0f) FloatingPawnMovementComponent->AddInputVector(GetDirectionVector(InputAxisValue.Z, EMovementDirection::Up));
	}
}

void ABotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABotPawn::HandleFloatingPawnMovement);
	}
}