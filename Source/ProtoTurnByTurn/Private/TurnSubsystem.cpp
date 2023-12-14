// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnSubsystem.h"
#include <Kismet/GameplayStatics.h>
#include <PlayerActionsScreen.h>
#include <TurnSettings.h>

void UTurnSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	currentPhase = Phases::EndPhase;
	currentTurn = 1;

	const UTurnSettings* TurnSettings = GetDefault<UTurnSettings>();
	debug = TurnSettings->debug;
	ActionPoints = TurnSettings->ActionPoints;
	VisionPoints = TurnSettings->VisionPoints;
	CancelRefundFactor = TurnSettings->CancelRefundFactor;
	DeletePoints = TurnSettings->DeletePoints;
	BuildPoints = TurnSettings->BuildPoints;
	PriorityPoints = TurnSettings->PriorityPoints;
	BlockPoints = TurnSettings->BlockPoints;
	StartNextPhase();
}


void UTurnSubsystem::StartNextPhase()
{
	//Not very usefull for now, just in case we need some rules to determine which entity should play next
	switch (currentPhase)
	{
	case Phases::PlayerPhase:
		currentPhase = Phases::CorruptionPhase;
		curActionPoints = 0;
		LastActions.Empty();
		StartCorruptionPhase();
		break;
	case Phases::CorruptionPhase:
		currentPhase = Phases::CivilizationPhase;
		StartCivilizationPhase();
		break;
	case Phases::CivilizationPhase:
		currentPhase = Phases::EndPhase;
		StartEndPhase();
		break;
	case Phases::EndPhase:
		currentPhase = Phases::PlayerPhase;
		StartPlayerPhase();
		break;
	default:
		break;
	}

}

void UTurnSubsystem::StartPlayerPhase()
{
	//Perform Player Phase
	curActionPoints = ActionPoints;
	
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Player is playing, turn number %d"), currentTurn));

	}

	OnStartPlayerPhase.ExecuteIfBound();
}

void UTurnSubsystem::StartCorruptionPhase()
{
	//Perform Corruption Phase
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Corruption is playing");
	}
	StartNextPhase();
}

void UTurnSubsystem::StartCivilizationPhase()
{
	//Perform Corruption Phase
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Civilization is playing");
	}
	StartNextPhase();
}

void UTurnSubsystem::StartEndPhase()
{
	//Perform all needs 
	currentTurn++;
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Ending Turn");
	}
	StartNextPhase();
}

void UTurnSubsystem::ActionDig()
{
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Digging");
		
	}
	

}

void UTurnSubsystem::ActionRaise()
{
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Raise");

	}
	
}

void UTurnSubsystem::ActionDelete()
{
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Delete");

	}
	
}

void UTurnSubsystem::ActionBuild()
{
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Build");

	}
	
}

void UTurnSubsystem::BuildTower()
{
	
	BuildComplete();
}

void UTurnSubsystem::BuildOutpost()
{
	
	BuildComplete();
}

void UTurnSubsystem::BuildFarm()
{
	
	BuildComplete();
}

void UTurnSubsystem::BuildHouse()
{

	BuildComplete();
}

void UTurnSubsystem::BuildComplete()
{
	OnBuildFinish.ExecuteIfBound();
}

void UTurnSubsystem::HandleActionRunningEvent(ActionTypes ActionType)
{
	OnActionRunning.ExecuteIfBound(ActionType);
}

void UTurnSubsystem::HandleBuildActionEvent(BuildTypes BuildType)
{
	//
	
	BuildComplete();
}

void UTurnSubsystem::ActionFinish(ActionTypes& Type, bool Completed)
{
	int factor;
	if (Completed) {
		factor = -1;
	}
	else {
		factor = 1;
	}
	switch (Type)
	{
	case ActionTypes::Vision:
		curActionPoints += factor * VisionPoints;
		break;
	case ActionTypes::Delete:
		curActionPoints += factor * DeletePoints;
		break;
	case ActionTypes::Build:
		curActionPoints += factor * BuildPoints;
		break;
	case ActionTypes::Priority:
		curActionPoints += factor * PriorityPoints;
		break;
	case ActionTypes::Block:
		curActionPoints += factor * BlockPoints;
		break;
	default:
		break;
	}
	Type = ActionTypes::None;
	OnActionFinish.ExecuteIfBound();
}

void UTurnSubsystem::PreviewActions()
{
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Previewing actions");

	}
}

FPastAction UTurnSubsystem::GetLastAction()
{
	return LastActions.Last();
}

void UTurnSubsystem::UndoLastAction()
{
	//Do something on the tile
	if (LastActions.Num() > 0) {
		FPastAction Action = GetLastAction();
		ActionFinish(Action.Type, false);
		LastActions.RemoveAt(LastActions.Num()-1);
	}
}

void UTurnSubsystem::AddLastAction(ActionTypes Type, AActor* Tile)
{
	FPastAction Action;
	Action.Tile = Tile;
	Action.Type = Type;
	LastActions.Emplace(Action);
}

void UTurnSubsystem::ActionPriority()
{
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Priority");

	}
	
}

void UTurnSubsystem::ActionBlock()
{
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Block");

	}

}

