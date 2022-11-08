// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraCompo");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("ProjectileTeleport", IE_Pressed, this, &ASCharacter::Teleport);

}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

FTransform ASCharacter::CalculateAim(float TraceRange)
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	
	FHitResult Hit;

	FVector CameraLocation = CameraComp->GetComponentToWorld().GetLocation();
	FVector CameraRotationVec = CameraComp->GetComponentToWorld().GetRotation().GetForwardVector();

	FVector End = CameraLocation + (CameraRotationVec * TraceRange);

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, CameraLocation, End, ObjectQueryParams);

	FRotator ProjectileRotator;

	if (bBlockingHit)
		ProjectileRotator = UKismetMathLibrary::FindLookAtRotation(HandLocation, Hit.ImpactPoint);
	else
		ProjectileRotator = UKismetMathLibrary::FindLookAtRotation(HandLocation, Hit.TraceEnd);

	FTransform SpawnTM = FTransform(ProjectileRotator, HandLocation);

	//DrawDebugLine(GetWorld(), CameraLocation, Hit.TraceEnd, FColor::Blue, false, 2.0f, 0, 2.0f);

	return SpawnTM;
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	ProjectileClass = MagicProjectileClass;

	GetWorldTimerManager().SetTimer(TimerHandler_PrimaryAttack, this, &ASCharacter::Attack_TimeElapsed, 0.2f);
}

void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);

	ProjectileClass = BlackholeProjectileClass;

	GetWorldTimerManager().SetTimer(TimerHandler_SecondaryAttack, this, &ASCharacter::Attack_TimeElapsed, 0.2f);
}

void ASCharacter::Attack_TimeElapsed()
{
	if (ensure(ProjectileClass))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FTransform ProjectileTransform = CalculateAim(10000.0f);

		GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileTransform, SpawnParams);
	}
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ASCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);

	ProjectileClass = DashProjectileClass;

	GetWorldTimerManager().SetTimer(TimerHandler_Dash, this, &ASCharacter::Attack_TimeElapsed, 0.2f);
}

