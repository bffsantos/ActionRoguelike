// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPickup.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASPickup : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickup();

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandler_Cooldown;

	void Cooldown_TimeElapsed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
