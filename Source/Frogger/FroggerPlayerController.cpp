// Fill out your copyright notice in the Description page of Project Settings.


#include "FroggerPlayerController.h"
#include "EnhancedInputSubsystems.h"

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

void AFroggerPlayerController::Server_Move_Implementation()
{
	OnServerMove();
}

bool AFroggerPlayerController::Server_Move_Validate()
{
	return true;
}
