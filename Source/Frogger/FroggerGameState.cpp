// Fill out your copyright notice in the Description page of Project Settings.


#include "FroggerGameState.h"

AFroggerGameState* AFroggerGameState::GetFroggerGameState(UObject* worldContext)
{
	UWorld* world = GEngine->GetWorldFromContextObject(worldContext, EGetWorldErrorMode::ReturnNull);
	return Cast<AFroggerGameState>(world->GetGameState());
}

void AFroggerGameState::Server_ReplicateMove(FVector TargetDestination, AFrogPawn* Frog)
{
	Multicast_ReplicateMove(TargetDestination, Frog);
}

void AFroggerGameState::Multicast_ReplicateMove_Implementation(FVector TargetDestination, AFrogPawn* Frog)
{
	Frog->AddActorWorldOffset(TargetDestination);
}
