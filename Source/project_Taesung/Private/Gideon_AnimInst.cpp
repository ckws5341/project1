// Fill out your copyright notice in the Description page of Project Settings.

#include "Gideon_AnimInst.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UGideon_AnimInst::UGideon_AnimInst()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> atk_montage(TEXT("/Game/UserCharacter_Gideon/Animation/Montage/Gideon_Attack_Montage.Gideon_Attack_Montage"));
	if (atk_montage.Succeeded())
		AttackMontage = atk_montage.Object;
}

void UGideon_AnimInst::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.f);

}

void UGideon_AnimInst::JumpToAttackMontageSection(int32 NewSection)
{
	CHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}
void UGideon_AnimInst::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
void UGideon_AnimInst::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}
FName UGideon_AnimInst::GetAttackMontageSectionName(int32 Section)
{
	CHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
