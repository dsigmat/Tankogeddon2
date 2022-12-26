#include "TankPawn.h"
#include "TankController.h"
#include "Cannon.h"
#include "Components/ArrowComponent.h"


class UInputComponent;
ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	RootComponent = BoxCollision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Body Mesh");
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>("Cannon Setup Point");
	CannonSetupPoint->SetupAttachment(TurretMesh);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();	

	TankController = Cast<ATankController>(GetController());
	SetupCannon(CannonClass);
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//MoveForward
	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector MovePosition = CurrentLocation + ForwardVector * MoveSpeed * ForwardMoveAxisValue * DeltaTime;
	SetActorLocation(MovePosition);

	//BodyRotation
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, RotateRightAxisValue, RotateInterpolationKey);
	//UE_LOG(LogTemp, Error, TEXT("CurrentRightAxisValue: %f, RotateRightAxisValue: %f, "), CurrentRightAxisValue, RotateRightAxisValue);

	float YawRotation = RotateRightAxisValue * RotationSpeed * DeltaTime;
	FRotator CurrentRotation = GetActorRotation();

	YawRotation += CurrentRotation.Yaw;
	FRotator NewRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(NewRotation);

	//TurretRotation

	if (TankController)
	{
		FVector MousePos = TankController->GetMousePos();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePos);
		FRotator TurretRotation = TurretMesh->GetComponentRotation();
		TargetRotation.Pitch = TurretRotation.Pitch;
		TargetRotation.Roll = TurretRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(TargetRotation, TurretRotation, TurretInterpolationKey));
	}
}

void ATankPawn::MoveForward(float Value)
{
	ForwardMoveAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RotateRightAxisValue = Value;
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannon)
{
	if (!newCannon)
	{
		return;
	}

	if (Cannon)
	{
		Cannon->Destroy();
	}
	
	FActorSpawnParameters Params;
	Params.Instigator = this;
	Params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(newCannon, Params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::ChangeCannon()
{
	TSubclassOf<ACannon> CachedCannon;
	CachedCannon = EquippedCannonClass;
	EquippedCannonClass = SecondCannonClass;
	SecondCannonClass = CachedCannon;
	//Swap(EquippedCannonClass, SecondCannonClass);
	SetupCannon(EquippedCannonClass);
}