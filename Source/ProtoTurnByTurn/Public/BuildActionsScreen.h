// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildActionsScreen.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTURNBYTURN_API UBuildActionsScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	AActor* TileToBuild;

	UFUNCTION(BlueprintImplementableEvent)
	void PlaceActionsToTileLocation(FVector2D TileLocationOnScreen);
};
