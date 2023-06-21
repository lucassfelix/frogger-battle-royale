// Fill out your copyright notice in the Description page of Project Settings.


#include "FroggerGameMode.h"

bool AFroggerGameMode::ReadyToStartMatch_Implementation()
{
	return Super::ReadyToStartMatch_Implementation();
//	return NumPlayers >= 2;
}

void AFroggerGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	if(HasMatchStarted())
	{
		ErrorMessage = ErrorMessageMatchInProgress;
	}

	if(NumPlayers >= MaxPlayers)
	{
		ErrorMessage = ErrorMessageMatchIsFull;
	}
	
}

void AFroggerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
