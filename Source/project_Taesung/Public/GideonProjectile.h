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
	void AttackCheck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Weapon) UStaticMeshComponent* pt1;
	UPROPERTY(VisibleAnywhere, Category = Trigger) UBoxComponent * Trigger;
	UPROPERTY(VisibleAnywhere, Category = Effect) UParticleSystemComponent* AttackEffect;
	AUserCharacter * ch = Cast<AUserCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	float projectileLifespan;
	FVector ptVec;
	bool bAttacked;
private :
	UFUNCTION() void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnEffectFinished(class UParticleSystemComponent* PSystem);

};
