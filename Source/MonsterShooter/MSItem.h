/*===============================================================================================================
Base class for all inventory items, should be blueprinted.
-----------------------------------------------------------------------------------------------------------------
Copyright (C) 2022 AethraVERSE. All Rights Reserved.
===============================================================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MSItem.generated.h"

UCLASS()
class MONSTERSHOOTER_API AMSItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMSItem();

	// Unique actor identifier to use for the new instance. It is text to be able to better search later. There shouldnТt be two the same items with the same ID!
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, AssetRegistrySearchable, meta = (DisplayPriority = "1"), Category = "Item")
		FName ShortID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayAfter = "ShortID"), Category = "Item")
		UTexture2D* Thumbnail;
	// Readable localized name of the parameter (Does NOT have to be unique!) Ц it can be УStrengthФ or УHealthФ whatever you like.This will be showed in UI.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "Name", DisplayAfter = "Thumbnail"), Category = "Item")
		FText DisplayName;
	// This is the long description that will be displayed in the menu.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayAfter = "DisplayName", MultiLine = "true"), Category = "Item")
		FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 Cost;

	// The number of instances of this item in the inventory, can never be below 1 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "MaxStackSize > 1", ClampMin = "1", UIMin = "1", ExposeOnSpawn = "true"), NoClear, Category = "Item")
		int32 Count;

	// Determines the maximum stack size that the player can make of this item. If the player has more of this item than this number, they will end up with multiple stacks. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (ClampMin = "1", UIMin = "1"), NoClear, Category = "Item")
		int32 MaxStackSize;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
		bool CanStackLimit() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "FreeStackSpace"), Category = "Item")
		int32 FreeStackSpace() const;

	// автоматически использовать при подборе
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		bool bAutoUse;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
		class UStaticMeshComponent* ItemMesh;
};
