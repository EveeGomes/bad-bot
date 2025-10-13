// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Bot.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABot::ABot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BotMesh;
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();

	// Get the only pawn spawned in the world and set it to TargetPawn.
	TArray<AActor*> PawnActors; // Can't be APawn pointer array since GetAllActorsOfClass only accepts AActor pointer array.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), PawnActors);

	if (PawnActors.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test: pawns in the level: %d"), PawnActors.Num());
		if (PawnActors[0]) TargetPawn = Cast<APawn>(PawnActors[0]);

		UE_LOG(LogTemp, Warning, TEXT("TargetPawn: %s"), *TargetPawn.GetName());
	}
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

