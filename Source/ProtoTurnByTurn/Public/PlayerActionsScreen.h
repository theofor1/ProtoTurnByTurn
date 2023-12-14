// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerActionsScreen.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTURNBYTURN_API UPlayerActionsScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ResetButtons();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtons();
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInfo(AActor* Tile);
	UFUNCTION(BlueprintImplementableEvent)
	void HideInfo();
};
