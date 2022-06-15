/*===============================================================================================================
Base class for all Characters. Designed to be blueprinted.
-----------------------------------------------------------------------------------------------------------------
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MSBaseCharacter.generated.h"

UCLASS()
class MONSTERSHOOTER_API AMSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMSBaseCharacter();
};
