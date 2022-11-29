// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SGameplayInterface.h"
#include "Components/SphereComponent.h"

// Sets default values
ASPickup::ASPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Pickup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;
}

void ASPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	AttributeComp->ApplyHealthChange(this, 100);
}

void ASPickup::ShowPickup()
{
	SetPickupState(true);
}

void ASPickup::HideAndCooldownPickup()
{
	SetPickupState(false);

	GetWorldTimerManager().SetTimer(TimerHandler_RespawnTimer, this, &ASPickup::ShowPickup, RespawnTime);
}

void ASPickup::SetPickupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(bNewIsActive, true);
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
	}
}

