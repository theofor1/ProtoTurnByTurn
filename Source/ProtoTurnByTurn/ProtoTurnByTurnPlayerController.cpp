// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProtoTurnByTurnPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "ProtoTurnByTurnCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AProtoTurnByTurnPlayerController::AProtoTurnByTurnPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	ActionIsRunning = false;
	BuildType = BuildTypes::None;
	LastHitActor = NULL;
}

void AProtoTurnByTurnPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	PlayerActionsScreen = CreateWidget<UPlayerActionsScreen>(this, PlayerActionsScreenClass);
	if (PlayerActionsScreen) {

		PlayerActionsScreen->AddToViewport();
	}
	TurnSubsystem = GetWorld()->GetSubsystem<UTurnSubsystem>();
	if (TurnSubsystem) {
		TurnSubsystem->OnActionRunning.BindUObject(this, &AProtoTurnByTurnPlayerController::ActionRunning);
		TurnSubsystem->OnActionFinish.BindUObject(this, &AProtoTurnByTurnPlayerController::ActionFinish);
		TurnSubsystem->OnBuildFinish.BindUObject(this, &AProtoTurnByTurnPlayerController::BuildFinish);
		TurnSubsystem->OnStartPlayerPhase.BindUObject(this, &AProtoTurnByTurnPlayerController::StartPhase);
	}
	PlayerCamera = static_cast<APlayerCamera*>(UGameplayStatics::GetActorOfClass(GetWorld(),APlayerCamera::StaticClass()));
}

void AProtoTurnByTurnPlayerController::Tick(float deltaTime)
{
	FHitResult Hit;
	
	bool bHitSuccessful = false;

	Super::Tick(deltaTime);
	if (ActionIsRunning) {
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		if (bHitSuccessful) {
			if (LastHitActor != Hit.GetActor()) {
				Hit.GetActor()->GetComponentByClass<UStaticMeshComponent>()->SetRenderCustomDepth(true);
				if (LastHitActor) {
					LastHitActor->GetComponentByClass<UStaticMeshComponent>()->SetRenderCustomDepth(false);
				}
				LastHitActor = Hit.GetActor();
				PlayerActionsScreen->UpdateInfo(LastHitActor);
			}
			
		}
		else {
			if (LastHitActor) {
				LastHitActor->GetComponentByClass<UStaticMeshComponent>()->SetRenderCustomDepth(false);
			}
			LastHitActor = NULL;
			PlayerActionsScreen->HideInfo();
		}
	}
}

void AProtoTurnByTurnPlayerController::BuildFinish()
{
	TurnSubsystem->AddLastAction(ActionType, BuildActionsScreen->TileToBuild);
	BuildActionsScreen->RemoveFromParent();
	TurnSubsystem->ActionFinish(ActionType, true);

}

void AProtoTurnByTurnPlayerController::ActionRunning(ActionTypes _ActionType)
{
	if (_ActionType == ActionType) {
		CancelAction();
	}
	else {
		ActionType = _ActionType;
		ActionIsRunning = true;
	}
}

void AProtoTurnByTurnPlayerController::BuildRunning(BuildTypes _BuildType)
{
	BuildType = _BuildType;
	//BuildComplete();
}

void AProtoTurnByTurnPlayerController::ActionFinish()
{
	PlayerActionsScreen->UpdateButtons();
	PlayerActionsScreen->HideInfo();
}

void AProtoTurnByTurnPlayerController::StartPhase()
{
	PlayerActionsScreen->ResetButtons();
}

void AProtoTurnByTurnPlayerController::CancelAction()
{
	if (ActionIsRunning) {
		ActionIsRunning = false;
		if (LastHitActor) {
			LastHitActor->GetComponentByClass<UStaticMeshComponent>()->SetRenderCustomDepth(false);
		}
		ActionType = ActionTypes::None;
	}
}

void AProtoTurnByTurnPlayerController::MoveCamera(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	if (PlayerCamera) {
		PlayerCamera->MoveCamera(-AxisValue);
	}
}

void AProtoTurnByTurnPlayerController::MoveCameraFromDraging()
{
	double DeltaX, DeltaY;
	GetInputMouseDelta(DeltaX, DeltaY);
	if (PlayerCamera) {
		PlayerCamera->isDraging = true;
		PlayerCamera->MoveCameraAlongOrbit(DeltaX, -DeltaY);
	}
}

void AProtoTurnByTurnPlayerController::StopMoveCameraFromDraging()
{
	if (PlayerCamera) {
		PlayerCamera->isDraging = false;
	}
}

void AProtoTurnByTurnPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AProtoTurnByTurnPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AProtoTurnByTurnPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AProtoTurnByTurnPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AProtoTurnByTurnPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AProtoTurnByTurnPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AProtoTurnByTurnPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AProtoTurnByTurnPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AProtoTurnByTurnPlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(CancelActionInput, ETriggerEvent::Triggered, this, &AProtoTurnByTurnPlayerController::CancelAction);
		EnhancedInputComponent->BindAction(ZoomCameraInput, ETriggerEvent::Triggered, this, &AProtoTurnByTurnPlayerController::MoveCamera);
		EnhancedInputComponent->BindAction(DragAndRotateInput, ETriggerEvent::Triggered, this, &AProtoTurnByTurnPlayerController::MoveCameraFromDraging);
		EnhancedInputComponent->BindAction(DragAndRotateInput, ETriggerEvent::Completed, this, &AProtoTurnByTurnPlayerController::StopMoveCameraFromDraging);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProtoTurnByTurnPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AProtoTurnByTurnPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful && ActionIsRunning)
	{
		CachedDestination = Hit.Location;
		//Action
		TileToModify = Hit.GetActor();
	}
	else {
		
	}

	if (TileToModify && ActionIsRunning) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%d : %s"), ActionType,*GetNameSafe(TileToModify)));
		if (ActionType == ActionTypes::Build) {
			ActionIsRunning = false;
			TileToModify->GetComponentByClass<UStaticMeshComponent>()->SetRenderCustomDepth(false);
			BuildActionsScreen = CreateWidget<UBuildActionsScreen>(this, BuildActionsScreenClass);
			
			if (BuildActionsScreen) {
				BuildActionsScreen->AddToViewport();
				BuildActionsScreen->TileToBuild = TileToModify;
				FVector2D LocationOnScreen;
				APlayerController::ProjectWorldLocationToScreen(TileToModify->GetActorLocation(), LocationOnScreen);
				BuildActionsScreen->PlaceActionsToTileLocation(LocationOnScreen);
			}
		}
		else {
		
				ActionIsRunning = false;
				TileToModify->GetComponentByClass<UStaticMeshComponent>()->SetRenderCustomDepth(false);
				TurnSubsystem->AddLastAction(ActionType, TileToModify);
				TurnSubsystem->ActionFinish(ActionType, true);
			
		}
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AProtoTurnByTurnPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AProtoTurnByTurnPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AProtoTurnByTurnPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
