/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#include "MonsterShooter.h"
#include "MSPickup.h"
#include "Components/CapsuleComponent.h"
#include "MSPlayerCharacter.h"

// Sets default values
AMSPickup::AMSPickup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CollisionComp"));
	CollisionComp->InitCapsuleSize(40.0f, 50.0f);
	CollisionComp->SetCollisionObjectType(COLLISION_PICKUP);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	RespawnDelay = 10.0f;
	bIsActive = false;
	bStartActive = true;
	bAllowRespawn = true;
	PickedUpBy = NULL;
}

// Called when the game starts or when spawned
void AMSPickup::BeginPlay()
{
	Super::BeginPlay();

	if (bStartActive)
	{
		RespawnPickup();
	}
}

void AMSPickup::NotifyActorBeginOverlap(class AActor* Other)
{
	Super::NotifyActorBeginOverlap(Other);
	PickupOnTouch(Cast<AMSPlayerCharacter>(Other));
}

bool AMSPickup::CanBePickedUp(class AMSPlayerCharacter* TestPawn) const
{
	return TestPawn != nullptr;//&& TestPawn->IsAlive();
}

void AMSPickup::GivePickupTo(class AMSPlayerCharacter* Pawn)
{}

void AMSPickup::PickupOnTouch(class AMSPlayerCharacter* Pawn)
{
	if (bIsActive && Pawn && /*Pawn->IsAlive() &&*/ !IsPendingKill())
	{
		if (CanBePickedUp(Pawn))
		{
			GivePickupTo(Pawn);
			PickedUpBy = Pawn;

			if (!IsPendingKill())
			{
				bIsActive = false;
				OnPickedUp();

				if (bAllowRespawn && RespawnDelay > 0.0f)
				{
					float RespawnTime = RespawnDelay + FMath::RandRange(0.0f, RespawnDelayRange);
					GetWorldTimerManager().SetTimer(TimerHandle_RespawnPickup, this, &AMSPickup::RespawnPickup, RespawnTime, false);
				}
				else
				{
					// Delete from level if respawn is not allowed
					Destroy();
				}
			}
		}
	}
}

void AMSPickup::RespawnPickup()
{
	bIsActive = true;
	PickedUpBy = NULL;
	OnRespawned();

	TSet<AActor*> OverlappingPawns;
	GetOverlappingActors(OverlappingPawns, AMSPlayerCharacter::StaticClass());

	for (AActor* OverlappingPawn : OverlappingPawns)
	{
		PickupOnTouch(CastChecked<AMSPlayerCharacter>(OverlappingPawn));
	}
}

void AMSPickup::OnPickedUp()
{
	/*if (PickupSound && PickedUpBy)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}*/

	OnPickedUpEvent();
}

void AMSPickup::OnRespawned()
{
	const bool bJustSpawned = CreationTime <= (GetWorld()->GetTimeSeconds() + 5.0f);
	/*if (RespawnSound && !bJustSpawned)
	{
		UGameplayStatics::PlaySoundAtLocation(this, RespawnSound, GetActorLocation());
	}*/

	OnRespawnEvent();
}