// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "project_Taesung.h"
#include "GameFramework/Character.h"
#include "BasicArmy_Lv1.generated.h"

UCLASS()
class PROJECT_TAESUNG_API ABasicArmy_Lv1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicArmy_Lv1();
	UPROPERTY(VisibleAnywhere, Category = Camera) USpringArmComponent* SpringArm;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
