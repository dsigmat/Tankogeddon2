#include "TankController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"

void ATankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	TankPawn = Cast<ATankPawn>(InPawn);
}



void ATankController::MoveForward(float Value)
{
	if (TankPawn)
	{
		TankPawn->MoveForward(Value);
	}
}

void ATankController::RotateRight(float Value)
{
	if (TankPawn)
	{
		TankPawn->RotateRight(Value);
	}
}

void ATankController::Fire()
{
	if (TankPawn)
	{
		TankPawn->Fire();
	}
}

void ATankController::FireSpecial()
{
	if (TankPawn)
	{
		TankPawn->FireSpecial();
	}
}

void ATankController::ChangeCannon()
{
	if (TankPawn)
	{
		TankPawn->ChangeCannon();
	}
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this , &ATankController::MoveForward);
	InputComponent->BindAxis("RotateRight", this , &ATankController::RotateRight);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed , this, &ATankController::Fire);
	InputComponent->BindAction("FireSpecial", EInputEvent::IE_Pressed, this, &ATankController::FireSpecial);
	InputComponent->BindAction("ChangeCannon", EInputEvent::IE_Pressed, this, &ATankController::ChangeCannon);
}

void ATankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector MouseDirection;
	DeprojectMousePositionToWorld(MousePos, MouseDirection);
	if (TankPawn)
	{
		FVector TankPosition = TankPawn->GetActorLocation();
		MousePos.Z = TankPosition.Z;
		FVector Dir = MousePos - TankPosition;
		Dir.Normalize();
		MousePos = TankPosition + Dir * 500;
	}
	
	//DrawDebugLine(GetWorld(), TankPosition, MousePos, FColor::Green, false, 0.1f, 0, 5);

	
}

ATankController::ATankController()
{
	bShowMouseCursor = true;
}