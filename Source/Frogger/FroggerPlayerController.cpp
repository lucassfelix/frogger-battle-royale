// Fill out your copyright notice in the Description page of Project Settings.


#include "FroggerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "FroggerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "FrogPawn.h"

void AFroggerPlayerController::BeginPlay()
{
	//Call base class
	Super::BeginPlay();

	bInitialized = false;
	
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(FrogMappingContext, 0);
	}
}

void AFroggerPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bInitialized)
	{
		LateInitialize();
	}
	
}

void AFroggerPlayerController::LateInitialize()
{
	if (const auto P = Cast<AFrogPawn>(GetPawn()))
	{
		FrogPawn = P;
		bInitialized = true;
	}
}


void AFroggerPlayerController::LaunchFrog(const float HorizontalRange, const float TimeToLand ,const EDir Direction)
{
	if(!bInitialized)
	{
		return;
	}
	
	const double Vx = HorizontalRange/TimeToLand;
	const double Vy = abs(GetWorld()->GetGravityZ()) * TimeToLand/2;

	UE_LOG(LogTemp, Warning, TEXT("Gravity = %f VY = %f"), abs(GetWorld()->GetGravityZ()) , Vy);


	FVector U;

	switch (Direction)
	{
	case Down:
		U = FVector(-Vx, 0, Vy);
		break;
	case Up:
		U = FVector(Vx, 0, Vy);
		break;
	case Right:
		U = FVector(0, Vx, Vy);
		break;
	case Left:
		U = FVector(0, -Vx, Vy);
		break;
	default:
		break;
	}

	//GetCharacter()->LaunchCharacter(U, false, false);
	Server_Move(U,FrogPawn);
}

void AFroggerPlayerController::Server_Move_Implementation(FVector TargetLocation, AFrogPawn* Frog)
{
	Frog->LaunchCharacter(TargetLocation, false, false);
	//AFroggerGameState::GetFroggerGameState(this)->Server_ReplicateMove(TargetLocation, Frog);
}

bool AFroggerPlayerController::Server_Move_Validate(FVector TargetLocation, AFrogPawn* Frog)
{
	return true;
}