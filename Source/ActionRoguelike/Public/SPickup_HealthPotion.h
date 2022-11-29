// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickup.h"
#include "SPickup_HealthPotion.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickup_HealthPotion : public ASPickup
{
	GENERATED_BODY()
	
public:

	ASPickup_HealthPotion();

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Componentes")
	UStaticMeshComponent* MeshComp;

};
