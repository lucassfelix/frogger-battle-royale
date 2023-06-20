// Fill out your copyright notice in the Description page of Project Settings.



#include "FrogPawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "VectorTypes.h"

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


	if(bMoving)
	{
		auto Alpha = FGenericPlatformMath::Min(TimePassed * 100 / TimeToMove,100.0);
		auto MoveTick = UE::Geometry::Lerp(StartPosition,Destination, Alpha);
		SetActorLocation(MoveTick);
		TimePassed += DeltaTime;

		if(Alpha == 100.0)
		{
			bMoving = false;
		}
	}
	
	
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

void AFrogPawn::BeginMove(const FVector& Direction)
{
	if(bMoving)
	{
		return;
	}
	StartPosition = GetActorLocation();
	Destination = StartPosition + Direction * MovementUnit;
	bMoving = true;
	TimePassed = 0;
}


void AFrogPawn::MoveUp()
{
	BeginMove(FVector(1,0,0));
}

void AFrogPawn::MoveDown()
{
	BeginMove(FVector(-1,0,0));
}

void AFrogPawn::MoveRight()
{
	BeginMove(FVector(0,1,0));
}

void AFrogPawn::MoveLeft()
{
	BeginMove(FVector(0,-1,0));
}


