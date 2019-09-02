// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "project_Taesung.h"
#include "UserCharacter.h"
#include "GameFramework/Actor.h"
#include "GideonProjectile.generated.h"

UCLASS()
class PROJECT_TAESUNG_API AGideonProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGideonProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Weapon) UStaticMeshComponent* pt1;
	AUserCharacter * ch = Cast<AUserCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	float projectileLifespan;
	FVector ptVec;
};
