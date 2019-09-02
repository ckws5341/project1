// Fill out your copyright notice in the Description page of Project Settings.

#include "GideonProjectile.h"
#include "Gideon_AnimInst.h"
// Sets default values
AGideonProjectile::AGideonProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pt1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PROJECTILE1"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	AttackEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	pt1 -> SetupAttachment(RootComponent);
	AttackEffect->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> Gideon_PT1(TEXT("/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_Black_Hole_Main.SM_Black_Hole_Main"));
	if (Gideon_PT1.Succeeded())
		pt1->SetStaticMesh(Gideon_PT1.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Atk_eff(TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_HitCharacter.P_Gideon_Primary_HitCharacter"));
	if (Atk_eff.Succeeded())
	{
		AttackEffect->SetTemplate(Atk_eff.Object);
		AttackEffect->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
		AttackEffect->bAutoActivate = false;
	}
	
	pt1->SetCollisionProfileName(TEXT("noCollision"));
	Trigger->SetCollisionProfileName(TEXT("Projectile"));
	Trigger->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	pt1->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	projectileLifespan = 0.f;


	bAttacked = false;
}

// Called when the game starts or when spawned
void AGideonProjectile::BeginPlay()
{
	Super::BeginPlay();
	ptVec = ch->GetActorForwardVector()*30.f;

}

void AGideonProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGideonProjectile::OnCharacterOverlap);
}
// Called every frame
void AGideonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	projectileLifespan += DeltaTime;
	if(projectileLifespan > 1.f)
		Destroy();

	if(!bAttacked)
		Trigger->AddRelativeLocation(ptVec);


}

void AGideonProjectile::AttackCheck()
{
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

void AGideonProjectile::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(project_Taesung, Warning, TEXT("Overlap"));
	AttackEffect->Activate(true);
	pt1->SetHiddenInGame(true, true);
	SetActorEnableCollision(false);
	bAttacked = true;
	AttackEffect->OnSystemFinished.AddDynamic(this, &AGideonProjectile::OnEffectFinished);
}

void AGideonProjectile::OnEffectFinished(UParticleSystemComponent *PSystem)
{
	Destroy();
}