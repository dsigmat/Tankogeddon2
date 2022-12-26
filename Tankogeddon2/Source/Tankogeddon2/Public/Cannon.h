#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDDON2_API ACannon : public AActor
{
	GENERATED_BODY()

public:
	ACannon();

	void Fire();
	void Reload();
	bool IsReadyToFire();
	void FireSpecial();

	FTimerHandle ReloadTimer;
	FTimerHandle BurstTimer;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float BurstInterval = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 BurstSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 Shells = 10;

public:
	virtual void Tick(float DeltaTime) override;

private:
	bool bReadyToFire = false;

	int32 CurrentBurts = 0;

	void Burst();
	void FireProjectile();
	void FireTrace();
};
