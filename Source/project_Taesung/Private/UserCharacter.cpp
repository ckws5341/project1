// Fill out your copyright notice in the Description page of Project Settings.

#include "UserCharacter.h"
#include "Gideon_AnimInst.h"
#include "GideonProjectile.h"

// Sets default values
AUserCharacter::AUserCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));
	SpringArm->TargetArmLength = 650.f;
	SpringArm->SetRelativeRotation(FRotator(0.f, 40.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKMESH(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon"));
	if (SKMESH.Succeeded())
		GetMesh()->SetSkeletalMesh(SKMESH.Object);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Gideon_AnimBlueprint.Gideon_AnimBlueprint_C"));
	if (ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(ANIM.Class);

	GetCharacterMovement()->JumpZVelocity = 600.f;

	IsAttacking = false;
	MaxCombo = 4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Gideon"));

}

// Called when the game starts or when spawned
void AUserCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
void AUserCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GidAnim = Cast<UGideon_AnimInst>(GetMesh()->GetAnimInstance());

	CHECK(nullptr != GidAnim);

	GidAnim->OnMontageEnded.AddDynamic(this, &AUserCharacter::OnAttackMontageEnded);

	GidAnim->OnNextAttackCheck.AddLambda([this]()->void {
		CanNextCombo = false;
		if (IsComboInputOn)
		{
			AttackStartComboState();
			GidAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});
	GidAnim->OnAttackHitCheck.AddUObject(this, &AUserCharacter::AttackCheck);
	
}
// Called every frame
void AUserCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AUserCharacter::AttackCheck()
{
	//AGideonProjectile * pt = Cast<AGideonProjectile>(UGameInstance::);
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation() - GetActorForwardVector() * 10.f,
		GetActorLocation() + GetActorForwardVector() * 10.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.f),
		Params);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
			UE_LOG(project_Taesung, Warning, TEXT("Hit Actor!"));
	}

}
// Called to bind functionality to input
void AUserCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AUserCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AUserCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AUserCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AUserCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AUserCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("Scale"), this, &AUserCharacter::Scale);
}

void AUserCharacter::UpDown(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AUserCharacter::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}
void AUserCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}
void AUserCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void AUserCharacter::Scale(float NewAxisValue)
{
	SpringArm->TargetArmLength -= (NewAxisValue*10.f);
	if (SpringArm->TargetArmLength <= 300.f) SpringArm->TargetArmLength = 300.f;
	else if(SpringArm->TargetArmLength >= 1000.f) SpringArm->TargetArmLength = 1000.f;
}
void AUserCharacter::Attack()
{
	if (IsAttacking)
	{
		CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
			IsComboInputOn = true;
	}
	else
	{
		CHECK(CurrentCombo == 0);
		AttackStartComboState();
		GidAnim->PlayAttackMontage();
		GidAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void AUserCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	CHECK(IsAttacking);
	CHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

void AUserCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));

	FName WeaponSocket(TEXT("hand_r"));
	auto Gid_projectile = GetWorld()->SpawnActor<AGideonProjectile>(GetMesh()->GetSocketLocation(WeaponSocket), GetMesh()->GetSocketRotation(WeaponSocket));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
	
}

void AUserCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}