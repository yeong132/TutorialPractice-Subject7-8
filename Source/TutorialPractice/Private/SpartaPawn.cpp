#include "SpartaPawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"

ASpartaPawn::ASpartaPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetSimulatePhysics(false);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
	SkeletalMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	MoveSpeed = 400.0f;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Look
				);
			}
		}
	}
}

void ASpartaPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;
	// 방향 유지
	FVector2D MoveVector = value.Get<FVector2D>();

	if (MoveVector.IsNearlyZero()) return;

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	UE_LOG(LogTemp, Warning, TEXT("Forward: %s"), *Forward.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Right: %s"), *Right.ToString());
	UE_LOG(LogTemp, Warning, TEXT("MoveVector.X: %f"), MoveVector.X);
	UE_LOG(LogTemp, Warning, TEXT("MoveVector.Y: %f"), MoveVector.Y);
	FVector MoveDirection = (Forward * MoveVector.X) + (Right * MoveVector.Y);
	FVector DeltaLocation = MoveDirection * MoveSpeed * GetWorld()->GetDeltaSeconds();

	AddActorWorldOffset(DeltaLocation, true);
}

void ASpartaPawn::Look(const FInputActionValue& Value)
{
	if (!Controller) return;

	FVector2D LookVector = Value.Get<FVector2D>();
	if (LookVector.IsNearlyZero()) return;

	const float MouseSensitivity = 100.0f;
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// 좌/우 회전 (Yaw): Pawn 본체 회전
	float YawRotation = LookVector.X * MouseSensitivity * DeltaTime;
	AddActorLocalRotation(FRotator(0.0f, YawRotation, 0.0f));

	// 위/아래 회전 (Pitch): SpringArm 회전
	float PitchRotation = LookVector.Y * MouseSensitivity * DeltaTime;
	FRotator SpringArmRotation = SpringArmComp->GetRelativeRotation();
	SpringArmRotation.Yaw += YawRotation;
	SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch - PitchRotation, -80.0f, 80.0f);
	SpringArmComp->SetRelativeRotation(SpringArmRotation);
}


