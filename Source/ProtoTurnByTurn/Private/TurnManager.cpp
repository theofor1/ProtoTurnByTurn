// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"

// Sets default values
ATurnManager::ATurnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	debug = false;
	ActionPoints = 5;
	
}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
	//currentPhase = Phases::EndPhase;
	currentTurn = 1;
	StartNextPhase();
	
}

// Called every frame
void ATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnManager::StartNextPhase()
{


}

void ATurnManager::StartPlayerPhase()
{
	//Perform Player Phase
	ActionPoints = 5;
	if (debug){
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Player is playing, turn number %d"), currentTurn));
	}
	
}

void ATurnManager::StartCorruptionPhase()
{
	//Perform Corruption Phase
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Corruption is playing");
	}
	StartNextPhase();
}

void ATurnManager::StartCivilizationPhase()
{
	//Perform Corruption Phase
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Civilization is playing");
	}
	StartNextPhase();
}

void ATurnManager::StartEndPhase()
{
	//Perform all needs 
	currentTurn++;
	if (debug) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Ending Turn");
	}
	StartNextPhase();
}

void ATurnManager::ActionDig()
{
}

void ATurnManager::ActionRaise()
{
}

void ATurnManager::ActionForest()
{
}

