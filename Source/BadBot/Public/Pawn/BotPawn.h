// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputMappingContext.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "BotPawn.generated.h"

UCLASS()
class BADBOT_API ABotPawn : public APawn
{
	GENERATED_BODY()

public:
	
	/***************** METHODS *****************/
	ABotPawn();
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/* INPUT */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMCBot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> Look;
	
	/* END INPUT */

	/***************** METHODS *****************/
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PawnMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovementComponent;

	/***************** METHODS *****************/
	FVector& GetRightInputVector(const FInputActionValue& InputActionValue);
	FVector& GetForwardInputVector(const FInputActionValue& InputActionValue);
	FVector& GetUpInputVector(const FInputActionValue& InputActionValue);

	FVector& GetDirectionVector(const FInputActionValue& InputActionValue, const FString& Direction);

	/**
	 * same: FVector DirectionScaled {0.0f};
	 *
	 * same: FVector InputAxisValue
	 * DirectionVector = Controller to call Get-Direction-Vector(ControllerRotation)
	 * DirectionScaled = DirectionVector * InputAxisValue.DirectionAxis
	 *
	 * return DirectionScaled
	 */
};