// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TurnSubsystem.generated.h"

/**
 * 
 */
UENUM()
enum class Phases : uint8 {
	PlayerPhase,
	CorruptionPhase,
	CivilizationPhase,
	EndPhase
};
UENUM()
enum class BuildTypes : uint8 {
	None,
	Tower,
	Outpost,
	Farm,
	House
};
UENUM()
enum class ActionTypes : uint8 {
	None,
	Vision,
	Cancel,
	Delete,
	Build,
	Priority,
	Block
};
USTRUCT(BlueprintType)
struct FPastAction {
	GENERATED_BODY()

	

UPROPERTY(BlueprintReadOnly)
	ActionTypes Type;
	UPROPERTY(BlueprintReadOnly)
	AActor* Tile;


};

DECLARE_DELEGATE_OneParam(FActionRunning,ActionTypes);
DECLARE_DELEGATE(FActionFinish);
DECLARE_DELEGATE(FBuildFinish);
DECLARE_DELEGATE(FStartPlayerPhase);

UCLASS()
class PROTOTURNBYTURN_API UTurnSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	
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
	void ActionDelete();
	UFUNCTION(BlueprintCallable)
	void ActionBuild();
	UFUNCTION(BlueprintCallable)
	void ActionPriority();
	UFUNCTION(BlueprintCallable)
	void ActionBlock();
	UFUNCTION(BlueprintCallable)
	void BuildTower();
	UFUNCTION(BlueprintCallable)
	void BuildOutpost();
	UFUNCTION(BlueprintCallable)
	void BuildFarm();
	UFUNCTION(BlueprintCallable)
	void BuildHouse();
	UFUNCTION(BlueprintCallable)
	void BuildComplete();
	UFUNCTION(BlueprintCallable)
	void HandleActionRunningEvent(ActionTypes ActionType);
	UFUNCTION(BlueprintCallable)
	void HandleBuildActionEvent(BuildTypes BuildType);

	UFUNCTION(BlueprintCallable)
	void ActionFinish(ActionTypes& Type, bool Completed);
	UFUNCTION(BlueprintCallable)
	void PreviewActions();
	UFUNCTION(BlueprintCallable)
	FPastAction GetLastAction();
	UFUNCTION(BlueprintCallable)
	void UndoLastAction();
	UFUNCTION(BlueprintCallable)
	void AddLastAction(ActionTypes Type, AActor* Tile);

public: //Variables
	UPROPERTY(BlueprintReadOnly)
	Phases currentPhase;
	FActionRunning OnActionRunning;
	FActionFinish OnActionFinish;
	FBuildFinish OnBuildFinish;
	FStartPlayerPhase OnStartPlayerPhase;

	UPROPERTY(BlueprintReadOnly)
	TArray<FPastAction> LastActions;

	UPROPERTY(BlueprintReadOnly)
	int currentTurn;
	UPROPERTY(BlueprintReadWrite)
	int ActionPoints;
	UPROPERTY(BlueprintReadOnly)
	int curActionPoints;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool debug;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int VisionPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CancelRefundFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DeletePoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BuildPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PriorityPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BlockPoints;
};
