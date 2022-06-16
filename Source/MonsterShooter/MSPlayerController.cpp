/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#include "MonsterShooter.h"
#include "MSPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/LocalPlayer.h"

AMSPlayerController::AMSPlayerController() 
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAxis("MoveForward/Backwards", this, &ThisClass::MoveForward);
	InputComponent->BindAxis("MoveRight/Left", this, &ThisClass::MoveRight);

	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &ThisClass::NextWeapon);
	InputComponent->BindAction("PrevWeapon", IE_Released, this, &ThisClass::PrevWeapon);

	// Bind fire event
	InputComponent->BindAction("Fire", IE_Pressed, this, &ThisClass::Fire);
	InputComponent->BindAction("MoveToCursor", IE_Pressed, this, &ThisClass::MoveToCursorPressed);
	InputComponent->BindAction("MoveToCursor", IE_Released, this, &ThisClass::MoveToCursorReleased);

	InputComponent->BindAction("Flashlight", IE_Pressed, this, &ThisClass::Flashlight);
	InputComponent->BindAction("InfoPanel", IE_Pressed, this, &ThisClass::InfoPanel);
	InputComponent->BindAction("QuickSlot1", IE_Pressed, this, &ThisClass::QuickSlot1);
	InputComponent->BindAction("QuickSlot2", IE_Pressed, this, &ThisClass::QuickSlot2);
	InputComponent->BindAction("QuickSlot3", IE_Pressed, this, &ThisClass::QuickSlot3);
	InputComponent->BindAction("QuickSlot4", IE_Pressed, this, &ThisClass::QuickSlot4);
	InputComponent->BindAction("QuickSlot5", IE_Pressed, this, &ThisClass::QuickSlot5);
	InputComponent->BindAction("QuickSlot6", IE_Pressed, this, &ThisClass::QuickSlot6);
	InputComponent->BindAction("QuickSlot7", IE_Pressed, this, &ThisClass::QuickSlot7);
	InputComponent->BindAction("QuickSlot8", IE_Pressed, this, &ThisClass::QuickSlot8);
	InputComponent->BindAction("QuickSlot9", IE_Pressed, this, &ThisClass::QuickSlot9);
	InputComponent->BindAction("Menu", IE_Pressed, this, &ThisClass::Menu);
}

void AMSPlayerController::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);
	MyCharacter = Cast<AMSBaseCharacter>(InPawn);
}

// Called when the game starts or when spawned
void AMSPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	DeltaTimeRef = DeltaTime;

	// keep updating the destination every tick while desired
	if (bMoveToCursor)
	{
		MoveToCursor();
	}
}

void AMSPlayerController::MoveForward(float Value)
{
	// Zero out pitch and roll, only move on plane
	const FRotator YawRotation(0, 1, 0);
	const FVector ForwardVector = YawRotation.Vector();
	
	if (MyCharacter)
		MyCharacter->AddMovementInput(ForwardVector, Value);
}

void AMSPlayerController::MoveRight(float Value)
{
	// Zero out pitch and roll, only move on plane
	const FRotator YawRotation(0, 1, 0);
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
	
	if (MyCharacter)
		MyCharacter->AddMovementInput(RightVector, Value);
}

void AMSPlayerController::NextWeapon()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("NextWeapon")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::PrevWeapon()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("PrevWeapon")), true, true, FLinearColor::Green, DeltaTimeRef);
}

void AMSPlayerController::Fire()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Fire")), true, true, FLinearColor::Green, DeltaTimeRef);
}

void AMSPlayerController::SetMouseCursorEnabled(bool bEnabled)
{
	//Set mouse cursor flag
	SetShowMouseCursor(bEnabled);

	//Place mouse in the center of the screen
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
	FIntPoint ScreenSize = Viewport->GetSizeXY();
	Viewport->SetMouse(ScreenSize.X / 2, ScreenSize.Y / 2);

	//Fix to prevent the cursor being restricted by the window border, thus preventing proper rotation by mouse movement
	if (!bEnabled)
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		return;
	}

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AMSPlayerController::MoveToCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
		UKismetSystemLibrary::PrintString(this, FString(TEXT("SetNewMoveDestination")), true, true, FLinearColor::Green, DeltaTimeRef);
	}
}

void AMSPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (MyCharacter)
	{
		float Distance = FVector::Dist(DestLocation, MyCharacter->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f) && (Distance < 10000.f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			UKismetSystemLibrary::PrintString(this, FString(TEXT("SimpleMoveToLocation")), true, true, FLinearColor::Green, DeltaTimeRef);
		}
	}	
}

void AMSPlayerController::MoveToCursorPressed()
{
	// set flag to keep updating destination until released
	bMoveToCursor = true;
	UKismetSystemLibrary::PrintString(this, FString(TEXT("MoveToCursorPressed")), true, true, FLinearColor::Green, DeltaTimeRef);
}

void AMSPlayerController::MoveToCursorReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToCursor = false;
	UKismetSystemLibrary::PrintString(this, FString(TEXT("MoveToCursorReleased")), true, true, FLinearColor::Green, DeltaTimeRef);
}

void AMSPlayerController::Flashlight()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Flashlight")), true, true, FLinearColor::Green, DeltaTimeRef);
}

void AMSPlayerController::InfoPanel()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("InfoPanel")), true, true, FLinearColor::Green, DeltaTimeRef);
}

void AMSPlayerController::QuickSlot1()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot1")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot2()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot2")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot3()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot3")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot4()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot4")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot5()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot5")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot6()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot6")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot7()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot7")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot8()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot8")), true, true, FLinearColor::Green, DeltaTimeRef);
}
void AMSPlayerController::QuickSlot9()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("QuickSlot9")), true, true, FLinearColor::Green, DeltaTimeRef);
}

void AMSPlayerController::Menu()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Menu")), true, true, FLinearColor::Green, DeltaTimeRef);
}