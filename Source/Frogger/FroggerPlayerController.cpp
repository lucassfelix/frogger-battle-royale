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