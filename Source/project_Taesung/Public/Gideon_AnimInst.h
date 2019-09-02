// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "project_Taesung.h"
#include "Animation/AnimInstance.h"
#include "Gideon_AnimInst.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
/**
 * 
 */
UCLASS()
class PROJECT_TAESUNG_API UGideon_AnimInst : public UAnimInstance
{
	GENERATED_BODY()

public :
	UGideon_AnimInst();
	//virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

public :
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

private:
	
	UFUNCTION() void AnimNotify_AttackHitCheck();
	UFUNCTION() void AnimNotify_NextAttackCheck();
	FName GetAttackMontageSectionName(int32 Section);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true)) UAnimMontage* AttackMontage;
	
	
	
};
