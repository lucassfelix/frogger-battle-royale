// Fill out your copyright notice in the Description page of Project Settings.


#include "FroggerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "FroggerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "FrogPawn.h"

void AFroggerPlayerController::BeginPlay()
{
	//Call base class
	Super::BeginPlay();

	bInitialized = false;
	
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(FrogMappingContext, 0);
	}
}

void AFroggerPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bInitialized)
	{
		LateInitialize();
	}
	
}

void AFroggerPlayerController::LateInitialize()
{
	if (const auto P = Cast<AFrogPawn>(GetPawn()))
	{
		FrogPawn = P;
		bInitialized = true;
	}
}


void AFroggerPlayerController::LaunchFrog(const float HorizontalRange, const float TimeToLand ,const EDir Direction)
{
	if(!bInitialized)
	{
		return;
	}
	
	const double Vx = HorizontalRange/TimeToLand;
	const double Vy = abs(GetWorld()->GetGravityZ()) * TimeToLand/2;

	FVector U;

	switch (Direction)
	{
	case Down:
		U = FVector(-Vx, 0, Vy);
		break;
	case Up:
		U = FVector(Vx, 0, Vy);
		break;
	case Right:
		U = FVector(0, Vx, Vy);
		break;
	case Left:
		U = FVector(0, -Vx, Vy);
		break;
	default:
		break;
	}

	//GetCharacter()->LaunchCharacter(U, false, false);
	Server_Move(U,FrogPawn);
	Server_Rotate(Direction,FrogPawn);
}

void AFroggerPlayerController::Server_Round_Implementation(FVector Location)
{
	FrogPawn->GetRootComponent()->SetWorldLocation(Location);
}

bool AFroggerPlayerController::Server_Round_Validate(FVector Location)
{
	return true;
}

void AFroggerPlayerController::Server_Impulse_Implementation(AMovingPlatform* Platform, float MovingX, float MovingY)
{
	auto Location = Platform->GetRootComponent()->GetComponentLocation();
	FrogPawn->GetRootComponent()->SetWorldLocation(FVector(Location.X,Location.Y,77.5f));
	UE_LOG(LogTemp,Warning,TEXT("Set to Vector = %f,%f,%f"),Location.X,Location.Y,77.7f);
}

bool AFroggerPlayerController::Server_Impulse_Validate(AMovingPlatform* Platform, float MovingX,float MovingY)
{
	return true;
}


void AFroggerPlayerController::Server_Rotate_Implementation(EDir Direction, AFrogPawn* Frog)
{
	switch (Direction) {
		case Down: Frog->FrogMesh->SetWorldRotation(FRotator(0,90,0)); break;
		case Up: Frog->FrogMesh->SetWorldRotation(FRotator(0,270,0)); break;
		case Right: Frog->FrogMesh->SetWorldRotation(FRotator(0,0,0)); break;
		case Left: Frog->FrogMesh->SetWorldRotation(FRotator(0,180,0)); break;
		case None: break;
		default: ;
	}
}

bool AFroggerPlayerController::Server_Rotate_Validate(EDir Direction, AFrogPawn* Frog)
{
	return true;
}

void AFroggerPlayerController::Server_Move_Implementation(FVector TargetLocation, AFrogPawn* Frog)
{
	Frog->LaunchCharacter(TargetLocation, false, false);
	//AFroggerGameState::GetFroggerGameState(this)->Server_ReplicateMove(TargetLocation, Frog);
}

bool AFroggerPlayerController::Server_Move_Validate(FVector TargetLocation, AFrogPawn* Frog)
{
	return true;
}