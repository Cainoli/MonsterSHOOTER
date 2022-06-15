/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#include "MonsterShooter.h"
#include "MSPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"

FName AMSPlayerCharacter::SpringArmCameraComponentName(TEXT("SpringArmCamComp"));
FName AMSPlayerCharacter::CharacterCameraComponentName(TEXT("CamComp"));

AMSPlayerCharacter::AMSPlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	// Disable on capsule collision to avoid double-dipping and receiving 2 overlaps when entering trigger zones etc.
	// Once from the mesh, and 2nd time from capsule
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight())));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	static FName MeshCollisionProfileName = "PhysicsActor";
	GetMesh()->SetCollisionProfileName(MeshCollisionProfileName);
	// Enabled on mesh to react to incoming projectiles
	GetMesh()->SetGenerateOverlapEvents(true);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmCameraComponent = CreateOptionalDefaultSubobject<USpringArmComponent>(SpringArmCameraComponentName);
	SpringArmCameraComponent->SetupAttachment(RootComponent);
	SpringArmCameraComponent->TargetArmLength = 1000;
	SpringArmCameraComponent->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArmCameraComponent->SetRelativeRotation(FRotator(-65.0f, -35.0f, 0.f));
	SpringArmCameraComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level	
	SpringArmCameraComponent->bUsePawnControlRotation = false;

	CharacterCameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(CharacterCameraComponentName);
	CharacterCameraComponent->SetupAttachment(SpringArmCameraComponent, USpringArmComponent::SocketName);
	CharacterCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	CharacterCameraComponent->FieldOfView = 90;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
