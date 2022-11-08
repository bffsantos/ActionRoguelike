// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASDashProjectile::ASDashProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandler_Teleport, this, &ASDashProjectile::ExplodeProjectile_TimeElapsed, 1.0f);
}

void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//SphereComp->OnComponentHit.AddDynamic(this, &ASBarrel::OnActorHit);
}

// Called every frame
void ASDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASDashProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void ASDashProjectile::ExplodeProjectile_TimeElapsed()
{
	ProjectileMovementComp->StopMovementImmediately();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, this->GetTransform());

	Teleport();
}

void ASDashProjectile::Teleport()
{
	GetWorldTimerManager().SetTimer(TimerHandler_Teleport, this, &ASDashProjectile::Teleport_TimeElapsed, 0.2f);
}

void ASDashProjectile::Teleport_TimeElapsed()
{
	GetInstigator()->TeleportTo(this->GetActorLocation(), this->GetActorRotation(), false, false);

	this->Destroy();
}
