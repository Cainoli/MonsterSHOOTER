/*===============================================================================================================
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#include "MonsterShooter.h"
#include "MSItem.h"

// Sets default values
AMSItem::AMSItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Itm_Mesh")));
	ItemMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	ItemMesh->Mobility = EComponentMobility::Movable;

	ShortID = "ITM";

	Count = 1;
	MaxStackSize = 1;
	Cost = 0;
	bAutoUse = true;
}

bool AMSItem::CanStackLimit() const
{
	return MaxStackSize >= 1;
}

int32 AMSItem::FreeStackSpace() const
{
	return FMath::Clamp(MaxStackSize - Count, 0, MaxStackSize);
}
