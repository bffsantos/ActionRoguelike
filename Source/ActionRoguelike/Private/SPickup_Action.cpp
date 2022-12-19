// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup_Action.h"
#include "SActionComponent.h"
#include "SAction.h"

void ASPickup_Action::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn && ActionToGrant))
	{
		return;
	}

	USActionComponent* ActionComp = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));
	
	if (ActionComp)
	{
		if (ActionComp->GetAction(ActionToGrant))
		{
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionToGrant));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			return;
		}

		ActionComp->AddAction(InstigatorPawn, ActionToGrant);
		HideAndCooldownPickup();
	}
}