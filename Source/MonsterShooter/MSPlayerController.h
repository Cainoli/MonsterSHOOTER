/*===============================================================================================================
Base class for PlayerController.
-----------------------------------------------------------------------------------------------------------------
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MSBaseCharacter.h"
#include "MSPlayerController.generated.h"

UCLASS()
class MONSTERSHOOTER_API AMSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	AMSPlayerController();

	UPROPERTY(BlueprintReadOnly, Category = "Base")
		AMSBaseCharacter* MyCharacter;

	float DeltaTimeRef;

	//~ Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	//~ End APlayerController Interface

	//~ Begin AController Interface
	virtual void SetPawn(APawn* InPawn) override;
	//~ End AController Interface

	// Called every frame.
	virtual void PlayerTick(float DeltaSeconds) override;

	// Enable the mouse cursor for point and click
	UFUNCTION(BlueprintCallable, Category = "UI")
		void SetMouseCursorEnabled(bool bEnabled = true);

	// True if the controlled character should navigate to the mouse cursor.
	bool bMoveToCursor;
	// Navigate player to the current mouse cursor location.
	void MoveToCursor();

	// Navigate player to the given world location.
	void SetNewMoveDestination(const FVector DestLocation);
	// Input handlers for SetDestination action.
	void MoveToCursorPressed();
	void MoveToCursorReleased();

	// Handles moving forward/backward
	virtual void MoveForward(float Value);
	// Handles stafing movement, left and right
	virtual void MoveRight(float Value);
	void NextWeapon();
	void PrevWeapon();
	void Fire();

	void Flashlight();
	void InfoPanel();
	void QuickSlot1();
	void QuickSlot2();
	void QuickSlot3();
	void QuickSlot4();
	void QuickSlot5();
	void QuickSlot6();
	void QuickSlot7();
	void QuickSlot8();
	void QuickSlot9();
	void Menu();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
