/*===============================================================================================================
Base class for GameMode, should be blueprinted.
-----------------------------------------------------------------------------------------------------------------
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MSGameMode.generated.h"

UCLASS()
class MONSTERSHOOTER_API AMSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	AMSGameMode();
};
