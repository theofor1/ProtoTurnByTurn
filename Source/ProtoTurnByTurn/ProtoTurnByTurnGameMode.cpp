// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProtoTurnByTurnGameMode.h"
#include "ProtoTurnByTurnPlayerController.h"
#include "ProtoTurnByTurnCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProtoTurnByTurnGameMode::AProtoTurnByTurnGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProtoTurnByTurnPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrints/Planet/BP_PlayerCamera"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}