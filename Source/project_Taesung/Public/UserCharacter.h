// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "project_Taesung.h"
#include "GameFramework/Character.h"
#include "UserCharacter.generated.h"

UCLASS()
class PROJECT_TAESUNG_API AUserCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUserCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera) USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera) UCameraComponent* Camera;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void Scale(float NewAxisValue);
	void Attack();
	void AttackCheck();
	UFUNCTION() void OnAttackMontageEnded(UAnimMontage* Montage, bool bIntrerrupted);

	void AttackStartComboState();
	void AttackEndComboState();

private :
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) bool IsAttacking;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) int32 MaxCombo;

	UPROPERTY() class UGideon_AnimInst * GidAnim;
};
