#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPawn.h"
#include "TankController.generated.h"


UCLASS()
class TANKOGEDDON2_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	ATankController();
	virtual void SetPawn(APawn* InPawn) override;

	FVector GetMousePos() {
		return MousePos;
	};
	
private:
	class ATankPawn* TankPawn;

	FVector MousePos;

	void MoveForward(float Value);
	void RotateRight(float Value);

	void Fire();
	void FireSpecial();

	void ChangeCannon();

	
};
