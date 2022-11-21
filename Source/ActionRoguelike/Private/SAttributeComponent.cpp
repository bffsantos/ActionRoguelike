// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
	MaxHealth = 100;
}

float USAttributeComponent::GetHealth()
{
	return Health;
}

float USAttributeComponent::GetMaxHealth()
{
	return MaxHealth;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	Health = FMath::Clamp(Health, 0, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

