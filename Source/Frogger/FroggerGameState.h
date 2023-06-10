// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FrogPawn.h"
#include "FroggerGameState.generated.h"

/**
 * 
 */
UCLASS()
class FROGGER_API AFroggerGameState : public AGameState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (WorldContext = "worldContext"))
	static AFroggerGameState* GetFroggerGameState(UObject* worldContext);

	void Server_ReplicateMove(FVector TargetDestination, AFrogPawn* Frog);

	UFUNCTION(NetMulticast, unreliable)
	void Multicast_ReplicateMove(FVector TargetDestination, AFrogPawn* Frog);

};
