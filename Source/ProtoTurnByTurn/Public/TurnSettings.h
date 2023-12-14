// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TurnSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Turn System Settings"))
class PROTOTURNBYTURN_API UTurnSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Draw debug (turn number and which entity is currently playing) on screen */
	UPROPERTY(Config,EditAnywhere, BlueprintReadWrite,Category=General)
	bool debug;

	/** Number of points player have */
	UPROPERTY(Config, EditAnywhere,BlueprintReadWrite, Category = PlayerTurn)
	int ActionPoints;

	/** Vision action point cost */
	UPROPERTY(Config,EditAnywhere, BlueprintReadWrite,Category=PlayerTurn)
	int VisionPoints;

	/** Cancel action point cost */
	UPROPERTY(Config,EditAnywhere, BlueprintReadWrite,Category=PlayerTurn)
	float CancelRefundFactor;

	/** Delete action point cost */
	UPROPERTY(Config,EditAnywhere, BlueprintReadWrite,Category=PlayerTurn)
	int DeletePoints;

	/** Build action point cost */
	UPROPERTY(Config,EditAnywhere, BlueprintReadWrite,Category=PlayerTurn)
	int BuildPoints;

	/** Priority action point cost */
	UPROPERTY(Config,EditAnywhere, BlueprintReadWrite,Category=PlayerTurn)
	int PriorityPoints;

	/** Block action point cost */
	UPROPERTY(Config,EditAnywhere, BlueprintReadWrite,Category=PlayerTurn)
	int BlockPoints;
};
