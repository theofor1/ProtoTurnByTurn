// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCamera.generated.h"

UCLASS()
class PROTOTURNBYTURN_API APlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCamera();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Classes)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	UStaticMeshComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	UStaticMeshComponent* CameraRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	USpringArmComponent* SpringArmMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	USpringArmComponent* SpringArmMid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	USpringArmComponent* SpringArmMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AActor> PlanetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MaxZoomDistanceFromPlanet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MinZoomDistanceFromPlanet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MaxMidZoomDistanceLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MidMinZoomDistanceLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MoveStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Repositionning)
	float PositionningSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Repositionning)
	float PositionningPrecision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float RotationPrecision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
	float FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float MaxZoomRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float MidZoomRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraRotation)
	float MinZoomRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MaxRotationPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MinRotationPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float PlanetRotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MaxFactorX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MinFactorX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MaxFactorY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanetRotation)
	float MinFactorY;


	AActor* Planet;
	float CurDistance;
	float MinSpringArmMaxLength;
	float MaxSpringArmMaxLength;
	float MinSpringArmMidLength;
	float MaxSpringArmMidLength;
	float MinSpringArmMinLength;
	float MaxSpringArmMinLength;

	USpringArmComponent* CurSpringArm;
	float CurMinSpringArmLength;
	float CurMaxSpringArmLength;

	float ArmLengthToReach;
	float LengthToAdd;
	float LengthToReach;
	float PitchToAdd;
	float RotationToReach;
	FVector PositionToAdd;
	FVector PositionToReach;
	bool CameraPositionning;
	bool CameraPositionningSetup;
	bool CameraInMovement;
	bool CameraInRotation;
	FVector InitialForwardVector;
	FRotator AfterRotation;
	FRotator BeforeRotation;
	FVector ForwardVectorBeforeRotation;
	FVector ForwardVectorAfterRotation;
	float DistanceBeforeRotation;

	float CurRotationX;
	float CurRotationY;

	bool isDraging;
	FVector2D PreviousMousePosition;

	APlayerController* PlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveCamera(float value);
	void MoveCameraAlongOrbit(float valueX, float valueY);
};
