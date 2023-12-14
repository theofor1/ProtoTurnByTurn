// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionWidget.h"
#include "Kismet/GameplayStatics.h"

UActionWidget::UActionWidget(const FObjectInitializer& Object) : Super(Object)
{
	Action = CreateWidget<UUserWidget>(GetWorld(), ButtonTemplateWidget);
	if (Action) {
		Action->AddToViewport();
	}
}


void UActionWidget::DoAction()
{
}
