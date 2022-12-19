// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickup.h"
#include "SPickup_Action.generated.h"

class USAction;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickup_Action : public ASPickup
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Powerup")
	TSubclassOf<USAction> ActionToGrant;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;
};
