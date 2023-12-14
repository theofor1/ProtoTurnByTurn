// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <TurnManager.h>
#include "ActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTURNBYTURN_API UActionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UActionWidget(const FObjectInitializer& Object);

protected:
	

	UFUNCTION()
	virtual void DoAction();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ButtonTemplateWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Cost;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* Action;
	UPROPERTY(BlueprintReadOnly)
	ATurnManager* TurnManager;
};
