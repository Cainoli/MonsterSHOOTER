/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "MSBaseCharacter.h"
#include "MSPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class MONSTERSHOOTER_API AMSPlayerCharacter : public AMSBaseCharacter
{
	GENERATED_BODY()

public:
	// Default UObject constructor.
	AMSPlayerCharacter();

	// Camera boom positioning the camera above the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetSpringArmCameraComponent, meta = (AllowPrivateAccess = "true"), Category = "Camera")
		class USpringArmComponent* SpringArmCameraComponent;
	// Name of the SpringArmCameraComponentComponent.
	static FName SpringArmCameraComponentName;
	// Returns SpringArmCameraComponent subobject
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Components")
		virtual USpringArmComponent* GetSpringArmCameraComponent() const { return SpringArmCameraComponent; }

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetCharacterCameraComponent, meta = (AllowPrivateAccess = "true"), Category = "Camera")
		class UCameraComponent* CharacterCameraComponent;
	// Name of the Camera component. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass).
	static FName CharacterCameraComponentName;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Components")
		virtual UCameraComponent* GetCharacterCameraComponent() const { return CharacterCameraComponent; }
};
