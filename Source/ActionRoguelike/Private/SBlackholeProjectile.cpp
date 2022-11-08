// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASBlackholeProjectile::ASBlackholeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(SphereComp);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 500.0f;
	RadialForceComp->ImpulseStrength = 0.0f;
	RadialForceComp->ForceStrength = -500.0f;
	RadialForceComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
}

// Called when the game starts or when spawned
void ASBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

