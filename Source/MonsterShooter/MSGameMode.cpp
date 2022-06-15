/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#include "MonsterShooter.h"
#include "MSGameMode.h"
#include "MSPlayerCharacter.h"
#include "MSPlayerController.h"

AMSGameMode::AMSGameMode()
{
	DefaultPawnClass = AMSPlayerCharacter::StaticClass();
	PlayerControllerClass = AMSPlayerController::StaticClass();
}