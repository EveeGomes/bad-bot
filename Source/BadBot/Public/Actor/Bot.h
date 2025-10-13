// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bot.generated.h"

UCLASS()
class BADBOT_API ABot : public AActor
{
	GENERATED_BODY()
	
public:	
	ABot();
	virtual void Tick(float DeltaTime) override;

	// Used to get a reference to the pawn controlled by the player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	TObjectPtr<APawn> TargetPawn;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UStaticMeshComponent> BotMesh;

};
