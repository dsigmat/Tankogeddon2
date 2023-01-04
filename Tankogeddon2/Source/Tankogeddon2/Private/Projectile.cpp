#include "Projectile.h"
#include "Components/SphereComponent.h"
#include <DamageTaker.h>
#include "GameStructs.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceeneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceeneComp;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(SceeneComp);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(SphereCollision);
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

void AProjectile::Move()
{
	FVector MovePosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(MovePosition);
}

void AProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (DamageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = GetOwner();
			damageData.DamageMaker = this;

			DamageTakerActor->TakeDamage(damageData);
		}
		else
		{
			OtherActor->Destroy();
		}
	}
	Destroy();
}

