// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FroggerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FROGGER_API AFroggerGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Connection")
	int MaxPlayers;

	//Returns true if ready to Start Match.
	virtual bool ReadyToStartMatch_Implementation() override;

	//Accept or reject a player attempting to join the server.
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	
	//Called every time a new player Joins the game
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly)
	FString ErrorMessageMatchInProgress;

	UPROPERTY(EditDefaultsOnly)
	FString ErrorMessageMatchIsFull;

	
	
};
