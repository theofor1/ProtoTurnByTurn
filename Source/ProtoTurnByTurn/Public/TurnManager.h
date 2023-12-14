// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"



UCLASS()
class PROTOTURNBYTURN_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	

	// Sets default values for this actor's properties
	ATurnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	//Functions
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartNextPhase();

	UFUNCTION()
	void StartPlayerPhase();
	UFUNCTION()
	void StartCorruptionPhase();
	UFUNCTION()
	void StartCivilizationPhase();
	UFUNCTION()
	void StartEndPhase();

	UFUNCTION(BlueprintCallable)
	void ActionDig();
	UFUNCTION(BlueprintCallable)
	void ActionRaise();
	UFUNCTION(BlueprintCallable)
	void ActionForest();

	
public: //Variables
	//UPROPERTY(BlueprintReadOnly)
	//Phases currentPhase;

	UPROPERTY(BlueprintReadOnly)
	int currentTurn;
	UPROPERTY(BlueprintReadOnly)
	int ActionPoints;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool debug;

};
