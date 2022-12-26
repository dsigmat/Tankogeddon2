// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "TankPawn.h"
#include "TankController.h"

ATankGameModeBase::ATankGameModeBase()
{
	DefaultPawnClass = ATankPawn::StaticClass();
	PlayerControllerClass = ATankController::StaticClass();



}
