// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrogPawn.h"
#include "FroggerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FROGGER_API AFroggerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	// Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FrogMappingContext;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnServerMove(FVector TargetLocation, AFrogPawn* Frog);
	
	UFUNCTION(Server, unreliable, WithValidation)
	void Server_Move(FVector TargetLocation, AFrogPawn* Frog);
	
};
