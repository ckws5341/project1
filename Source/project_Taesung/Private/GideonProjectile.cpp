// Fill out your copyright notice in the Description page of Project Settings.

#include "GideonProjectile.h"

// Sets default values
AGideonProjectile::AGideonProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pt1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PROJECTILE1"));
	RootComponent = pt1;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Gideon_PT1(TEXT("/Game/ParagonGideon/FX/Meshes/Heroes/Gideon/SM_Black_Hole_Main.SM_Black_Hole_Main"));
	if (Gideon_PT1.Succeeded())
		pt1->SetStaticMesh(Gideon_PT1.Object);
	pt1->SetCollisionProfileName(TEXT("NoCollision"));
	pt1->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	projectileLifespan = 0.f;
}

// Called when the game starts or when spawned
void AGideonProjectile::BeginPlay()
{
	Super::BeginPlay();
	ptVec = ch->GetActorForwardVector()*30.f;

}

// Called every frame
void AGideonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	projectileLifespan += DeltaTime;
	if(projectileLifespan > 1.f)
		Destroy();

	pt1->AddRelativeLocation(ptVec);
}


