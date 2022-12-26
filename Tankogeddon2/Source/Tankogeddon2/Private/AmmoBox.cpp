#include "AmmoBox.h"
#include <TankPawn.h>

AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceeneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceeneComp;

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo mesh"));
	AmmoMesh->SetupAttachment(SceeneComp);
	AmmoMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
	AmmoMesh->SetCollisionProfileName("OverlapAll");
	AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AmmoMesh->SetGenerateOverlapEvents(true);
}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{
		TankPawn->SetupCannon(CannonClass);
	}
	Destroy();
}