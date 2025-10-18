// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"

#include "Pawn/BotPawn.h"

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
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				EnhancedInputSubsystem->AddMappingContext(IMCBot, 0);
			}
		}	
	}
}

FVector& ABotPawn::GetRightInputVector(const FInputActionValue& InputActionValue)
{
	FVector RightVectorScaled{ 0.0f };
	
	if (const AController* Controller = GetController())
	{
		FVector RightVector = UKismetMathLibrary::GetRightVector(Controller->GetControlRotation());
		const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
		
		RightVectorScaled = RightVector * InputAxisValue.X;
	}
	
	return RightVectorScaled;
}

FVector& ABotPawn::GetForwardInputVector(const FInputActionValue& InputActionValue)
{
	FVector ForwardVectorScaled{ 0.0f };

	if (const AController* Controller = GetController())
	{
		FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Controller->GetControlRotation());
		ForwardVectorScaled = ForwardVector * InputAxisValue.Y;
	}

	return ForwardVectorScaled;
}

FVector& ABotPawn::GetUpInputVector(const FInputActionValue& InputActionValue)
{
	FVector UpVectorScaled{ 0.0f };

	if (const AController* Controller = GetController())
	{
		FVector InputAxisValue = InputActionValue.Get<FVector>();
		FVector UpVector = UKismetMathLibrary::GetUpVector(Controller->GetControlRotation());
		UpVectorScaled = UpVector * InputAxisValue.Z;
	}

	return UpVectorScaled;
}

FVector& ABotPawn::GetDirectionVector(const FInputActionValue& InputActionValue, const FString& Direction)
{
	FVector DirectionVectorScaled{ 0.0f };

	if (const AController* Controller = GetController())
	{
		FVector InputAxisValue = InputActionValue.Get<FVector>();

		switch (Direction)
		{
			case FString("Right"):
				DirectionVectorScaled = UKismetMathLibrary::GetRightVector(Controller->GetControlRotation()) * InputAxisValue.X;
				break;
			case FString("Forward"):
				DirectionVectorScaled = UKismetMathLibrary::GetForwardVector(Controller->GetControlRotation()) * InputAxisValue.Y;
				break;
			case FString("Up"):
				DirectionVectorScaled = UKismetMathLibrary::GetUpVector(Controller->GetControlRotation()) * InputAxisValue.Z;
				break;
		}
	}

	return DirectionVectorScaled;
}

void ABotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

