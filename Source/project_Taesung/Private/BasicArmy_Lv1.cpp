// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicArmy_Lv1.h"


// Sets default values
ABasicArmy_Lv1::ABasicArmy_Lv1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, 90.f, 0.f));
	SpringArm->TargetArmLength = 650.f;
	SpringArm->SetRelativeRotation(FRotator(0.f, 40.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKMESH(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon"));
	if (SKMESH.Succeeded())
		GetMesh()->SetSkeletalMesh(SKMESH.Object);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Gideon_AnimBlueprint.Gideon_AnimBlueprint_C"));
	if (ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(ANIM.Class);

	GetCharacterMovement()->JumpZVelocity = 600.f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("noCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("Army"));

}

// Called when the game starts or when spawned
void ABasicArmy_Lv1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicArmy_Lv1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicArmy_Lv1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

