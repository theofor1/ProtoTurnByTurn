// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PlayerCameraSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Player Camera Settings"))
class PROTOTURNBYTURN_API UPlayerCameraSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	/** The class of the Planet blueprint */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AActor> PlanetClass;

	/** Maximum camera distance of the planet */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MaxZoomDistanceFromPlanet = 20000;

	/** Minimum camera distance of the planet */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MinZoomDistanceFromPlanet;

	/** Distance where the camera switch between Max/Mid zoom mode (rotation) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MaxMidZoomDistanceLevel;

	/** Distance where the camera switch between Mid/Min zoom mode (rotation) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MidMinZoomDistanceLevel;

	/** Strength of the zoom (i.e distance at each input)*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MoveStrength;

	/** Speed of the camera zoom */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MoveSpeed;

	/** Speed of the camera when repositionning (after rotation, to keep same object in middle of screen) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Repositionning)
	float PositionningSpeed;

	/** Precision of the camera when repositionning (after rotation, to keep same object in middle of screen) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Repositionning)
	float PositionningPrecision;

	/** Speed of the camera rotation  */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float RotationSpeed;

	/** Precision of the camera rotation  */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float RotationPrecision;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float FOV;

	/** Camera rotation in Max zoom mode */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float MaxZoomRotation;

	/** Camera rotation in Mid zoom mode */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float MidZoomRotation;

	/** Camera rotation in Min zoom mode */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float MinZoomRotation;

	/** Max pitch value to reach, to avoid be upside down (90 = align with north pole) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MaxRotationPitch;

	/** Min pitch value to reach, to avoid be upside down (-90 = align with south pole) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MinRotationPitch;

	/** Speed of the camera when rotating around planet */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float PlanetRotationSpeed;

	/** Mouse max factor (right) position to trigger camera rotation around planet (value < 1) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MaxFactorX;

	/** Mouse min factor (left) position to trigger camera rotation around planet (value > 0) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MinFactorX;

	/** Mouse max factor (up) position to trigger camera rotation around planet (value < 1) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MaxFactorY;

	/** Mouse min factor (down) position to trigger camera rotation around planet (value > 0) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MinFactorY;


};
