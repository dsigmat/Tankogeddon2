#include "Turret.h"
#include <Components\BoxComponent.h>
#include <Components\StaticMeshComponent.h>
#include "Components/ArrowComponent.h"
#include "Engine/StaticMesh.h"


ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;

	HitCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = HitCollision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(HitCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>("CannonSetupPoint");
	CannonSetupPoint->SetupAttachment(TurretMesh);

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);

	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::Destroyed()
{
}

void ATurret::Targeting()
{
}

void ATurret::RotateToPlayer()
{
}

bool ATurret::IsPlayerInRange()
{
	return false;
}

bool ATurret::CanFire()
{
	return false;
}

void ATurret::Fire()
{
}

