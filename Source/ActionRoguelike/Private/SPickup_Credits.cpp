// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup_Credits.h"
#include "SPlayerState.h"


ASPickup_Credits::ASPickup_Credits()
{
	CreditsAmount = 80;
}

void ASPickup_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldownPickup();
	}
}
