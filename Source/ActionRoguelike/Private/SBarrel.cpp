// Fill out your copyright notice in the Description page of Project Settings.


#include "SBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASBarrel::ASBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	StaticMeshComp->SetSimulatePhysics(true); 
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ASBarrel::OnHit);
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 700.0f;
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->ForceStrength = 10.0f;
	RadialForceComp->SetupAttachment(StaticMeshComp);
}

// Called when the game starts or when spawned
void ASBarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}

