// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup_HealthPotion.h"
#include "SAttributeComponent.h"


ASPickup_HealthPotion::ASPickup_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ASPickup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetMaxHealth()))
		{
			HideAndCooldownPickup();
		}

	}
}
