// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "GameFramework/Actor.h"
#include "SDashProjectile.generated.h"

class UParticleSystem;

UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASDashProjectile();

protected:

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* Explosion;

	FTimerHandle TimerHandler_Teleport;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void ExplodeProjectile_TimeElapsed();
	
	void Teleport();

	void Teleport_TimeElapsed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
