// Fill out your copyright notice in the Description page of Project Settings.


#include "FroggerGameState.h"

void AFroggerGameState::TravelToGame()
{
	GetWorld()->ServerTravel(GameMapName,false,false);
}
