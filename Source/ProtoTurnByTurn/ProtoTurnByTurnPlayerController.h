// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include <PlayerActionsScreen.h>
#include <BuildActionsScreen.h>
#include <TurnSubsystem.h>
#include <PlayerCamera.h>

#include "InputAction.h"
#include "ProtoTurnByTurnPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;



DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AProtoTurnByTurnPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProtoTurnByTurnPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CancelActionInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomCameraInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DragAndRotateInput;


	UPROPERTY(BlueprintReadOnly)
	bool ActionIsRunning;
	ActionTypes ActionType;
	BuildTypes BuildType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPlayerActionsScreen> PlayerActionsScreenClass;
	UPlayerActionsScreen* PlayerActionsScreen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBuildActionsScreen> BuildActionsScreenClass;
	UBuildActionsScreen* BuildActionsScreen;

	UTurnSubsystem* TurnSubsystem;
	APlayerCamera* PlayerCamera;

	
	void BuildFinish();
	void ActionRunning(ActionTypes ActionType);
	void BuildRunning(BuildTypes BuildType);
	void ActionFinish();
	void StartPhase();
	void CancelAction();
	void MoveCamera(const FInputActionValue& Value);
	void MoveCameraFromDraging();
	void StopMoveCameraFromDraging();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	void Tick(float deltaTime) override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;
	AActor* TileToModify;
	AActor* LastHitActor;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


