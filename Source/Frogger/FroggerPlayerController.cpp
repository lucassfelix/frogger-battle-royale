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

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(FrogMappingContext, 0);
	}
}

void AFroggerPlayerController::Server_Move_Implementation(FVector TargetLocation, AFrogPawn* Frog)
{
	//OnServerMove(TargetLocation);

	AFroggerGameState::GetFroggerGameState(this)->Server_ReplicateMove(TargetLocation, Frog);
}

bool AFroggerPlayerController::Server_Move_Validate(FVector TargetLocation, AFrogPawn* Frog)
{
	return true;
}