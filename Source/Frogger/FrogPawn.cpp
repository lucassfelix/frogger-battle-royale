// Fill out your copyright notice in the Description page of Project Settings.



#include "FrogPawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AFrogPawn::AFrogPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFrogPawn::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AFrogPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFrogPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveUpInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveUp);
		EnhancedInputComponent->BindAction(MoveDownInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveDown);
		EnhancedInputComponent->BindAction(MoveLeftInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveLeft);
		EnhancedInputComponent->BindAction(MoveRightInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveRight);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast failed!"));
	}

}

void AFrogPawn::MoveUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Moveu para cima!"));
}

void AFrogPawn::MoveDown()
{
	UE_LOG(LogTemp, Warning, TEXT("Moveu para baixo!"));

}

void AFrogPawn::MoveLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("Moveu para esquerda!"));

}

void AFrogPawn::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("Moveu para direita!"));

}

