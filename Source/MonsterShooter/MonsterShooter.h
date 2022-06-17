/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#pragma once

#include "CoreMinimal.h"

// when you modify this, please note that this information can be saved with instances
// also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list
#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_PICKUP		ECC_GameTraceChannel3