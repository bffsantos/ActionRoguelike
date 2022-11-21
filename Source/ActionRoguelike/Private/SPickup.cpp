// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SGameplayInterface.h"

// Sets default values
ASPickup::ASPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ASPickup::OnActorOverlap);

}

void ASPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	AttributeComp->ApplyHealthChange(100);
}

// Called when the game starts or when spawned
void ASPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPickup::Cooldown_TimeElapsed()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ASPickup::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (AttributeComp && AttributeComp->GetHealth() < AttributeComp->GetMaxHealth())
	{
		APawn* Pawn = Cast<APawn>(OtherActor);

		ISGameplayInterface::Execute_Interact(this, Pawn);

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);

		GetWorldTimerManager().SetTimer(TimerHandler_Cooldown, this, &ASPickup::Cooldown_TimeElapsed, 10.0f);
	}
}

