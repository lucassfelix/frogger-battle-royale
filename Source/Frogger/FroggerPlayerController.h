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

	virtual void Tick(float DeltaSeconds) override;

	void LateInitialize();

	UPROPERTY(BlueprintReadOnly)
	AFrogPawn* FrogPawn;

	bool bInitialized;
	
	void LaunchFrog(const float HorizontalRange, const float TimeToLand, const EDir Direction);

	UFUNCTION(BlueprintImplementableEvent)
	void OnServerMove(FVector TargetLocation, AFrogPawn* Frog);
	
	UFUNCTION(Server, reliable, WithValidation)
	void Server_Move(FVector TargetLocation, AFrogPawn* Frog);

	UFUNCTION(Server, reliable, WithValidation)
	void Server_Rotate(EDir Direction, AFrogPawn* Frog);

	UFUNCTION(Server, unreliable, WithValidation)
	void Server_Impulse(AMovingPlatform* Platform,float MovingX,float MovingY);

	UFUNCTION(Server, reliable, WithValidation)
	void Server_Round(FVector Location);
	
};
