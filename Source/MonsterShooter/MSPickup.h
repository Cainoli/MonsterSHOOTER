/*===============================================================================================================
Base class for pickup objects that can be placed in the world.
-----------------------------------------------------------------------------------------------------------------
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MSPickup.generated.h"

class UCapsuleComponent;
class AMSPlayerCharacter;

UCLASS()
class MONSTERSHOOTER_API AMSPickup : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	

	// Pickup on touch
	virtual void NotifyActorBeginOverlap(class AActor* Other) override;

	// Check if pawn can use this pickup
	virtual bool CanBePickedUp(class AMSPlayerCharacter* MyPawn) const;

	// Sphere collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* CollisionComp;
	/*// sound played when player picks it up
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* PickupSound;

	// sound played on respawn
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* RespawnSound;*/

	// Immediately spawn on begin play
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
		bool bStartActive;

	// Will this item ever respawn
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
		bool bAllowRespawn;

	// how long it takes to respawn?
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
		float RespawnDelay;
	// Extra delay randomly applied on the respawn timer
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
		float RespawnDelayRange;

	// is it ready for interactions?
	UPROPERTY(Transient)
		bool bIsActive;

	// The character who has picked up this pickup
	UPROPERTY(Transient)
		AMSPlayerCharacter* PickedUpBy;

	// Handle for efficient management of RespawnPickup timer
	FTimerHandle TimerHandle_RespawnPickup;

	// Give pickup
	virtual void GivePickupTo(class AMSPlayerCharacter* Pawn);

	// Handle touches
	void PickupOnTouch(class AMSPlayerCharacter* Pawn);

	// Show and enable pickup
	virtual void RespawnPickup();

	// Show effects when pickup disappears
	virtual void OnPickedUp();

	// Show effects when pickup appears
	virtual void OnRespawned();

	// Blueprint event: Pickup disappears
	UFUNCTION(BlueprintImplementableEvent)
		void OnPickedUpEvent();

	// Blueprint event: Pickup appears
	UFUNCTION(BlueprintImplementableEvent)
		void OnRespawnEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
