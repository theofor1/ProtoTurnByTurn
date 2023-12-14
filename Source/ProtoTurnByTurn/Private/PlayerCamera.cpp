// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <PlayerCameraSettings.h>

// Sets default values
APlayerCamera::APlayerCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	SpringArmMax = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm for Max Zoom"));
	SpringArmMax->SetupAttachment(Root);
	SpringArmMid = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm for Mid Zoom"));
	SpringArmMid->SetupAttachment(Root);
	SpringArmMin = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm for Min Zoom"));
	SpringArmMin->SetupAttachment(Root);
	CameraRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraRoot"));
	CameraRoot->SetupAttachment(Root);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraRoot);
	
	
}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	//Get values from Config file
	const UPlayerCameraSettings* PCSettings = GetDefault<UPlayerCameraSettings>();
	PlanetClass = PCSettings->PlanetClass;
	MaxZoomDistanceFromPlanet = PCSettings->MaxZoomDistanceFromPlanet;
	MinZoomDistanceFromPlanet = PCSettings->MinZoomDistanceFromPlanet;
	MaxMidZoomDistanceLevel = PCSettings->MaxMidZoomDistanceLevel;
	MidMinZoomDistanceLevel = PCSettings->MidMinZoomDistanceLevel;
	MoveStrength = PCSettings->MoveStrength;
	MoveSpeed = PCSettings->MoveSpeed;
	PositionningSpeed = PCSettings->PositionningSpeed;
	PositionningPrecision = PCSettings->PositionningPrecision;
	RotationSpeed = PCSettings->RotationSpeed;
	RotationPrecision = PCSettings->RotationPrecision;
	FOV = PCSettings->FOV;
	MaxZoomRotation = PCSettings->MaxZoomRotation;
	MidZoomRotation = PCSettings->MidZoomRotation;
	MinZoomRotation = PCSettings->MinZoomRotation;
	MaxRotationPitch = PCSettings->MaxRotationPitch;
	MinRotationPitch = PCSettings->MinRotationPitch;
	PlanetRotationSpeed = PCSettings->PlanetRotationSpeed;
	MaxFactorX = PCSettings->MaxFactorX;
	MinFactorX = PCSettings->MinFactorX;
	MaxFactorY = PCSettings->MaxFactorY;
	MinFactorY = PCSettings->MinFactorY;

	CurRotationX = 0;
	CurRotationY = 0;

	Camera->SetFieldOfView(FOV);
	
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 100000;
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Camera)) {
		if (Hit.GetActor()->IsA(PlanetClass)) {
			//Save planet
			Planet = Hit.GetActor();

			//Set Location at beginning distance
			FVector Location = Hit.ImpactPoint;
			SetActorLocation(Location);
			InitialForwardVector = GetActorForwardVector();
			//CurDistance = FVector::Distance(Hit.ImpactPoint, GetActorLocation());
			DrawDebugPoint(GetWorld(), GetActorLocation(), 1, FColor::Red, true);
			
			//Spring arm max zoom setup
			SpringArmMax->AddRelativeRotation(FRotator(MaxZoomRotation, 0, 0));
			MinSpringArmMaxLength = MaxMidZoomDistanceLevel;
			MaxSpringArmMaxLength = MaxZoomDistanceFromPlanet;
			SpringArmMax->TargetArmLength = MaxSpringArmMaxLength;
			CurDistance = SpringArmMax->TargetArmLength;
			RotationToReach = MaxZoomRotation;
			CurSpringArm = SpringArmMax;
			CurMinSpringArmLength = MinSpringArmMaxLength;
			CurMaxSpringArmLength = MaxSpringArmMaxLength;
			CameraRoot->AttachToComponent(SpringArmMax, FAttachmentTransformRules::KeepRelativeTransform);

			//Spring arm mid zoom setup
			SpringArmMid->AddRelativeRotation(FRotator(MidZoomRotation, 0, 0));
			MinSpringArmMidLength = MidMinZoomDistanceLevel;
			MaxSpringArmMidLength = MaxMidZoomDistanceLevel;
			SpringArmMid->TargetArmLength = MaxSpringArmMidLength;
			

			//Spring arm min zoom setup
			SpringArmMin->AddRelativeRotation(FRotator(MinZoomRotation, 0, 0));
			MinSpringArmMinLength = MinZoomDistanceFromPlanet;
			MaxSpringArmMinLength = MidMinZoomDistanceLevel;
			SpringArmMin->TargetArmLength = MaxSpringArmMinLength;
			
		}

		/*
		DrawDebugLine(GetWorld(), SpringArmMax->GetComponentLocation() - SpringArmMax->GetForwardVector() * SpringArmMax->TargetArmLength, SpringArmMax->GetComponentLocation() - SpringArmMax->GetForwardVector() * MinSpringArmMaxLength, FColor::Red, true);
		DrawDebugLine(GetWorld(), SpringArmMid->GetComponentLocation() - SpringArmMid->GetForwardVector() * SpringArmMid->TargetArmLength, SpringArmMid->GetComponentLocation() - SpringArmMid->GetForwardVector() * MinSpringArmMidLength, FColor::Blue, true);
		DrawDebugLine(GetWorld(), SpringArmMin->GetComponentLocation() - SpringArmMin->GetForwardVector() * SpringArmMin->TargetArmLength, SpringArmMin->GetComponentLocation() - SpringArmMin->GetForwardVector() * MinSpringArmMinLength, FColor::Yellow, true);
		*/
	}

	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PreviousMousePosition = FVector2D(-1,-1);
}

// Called every frame
void APlayerCamera::Tick(float DeltaTime)
{
	
	FRotator CurRotation ;
	FRotator NewRotation;
	
	Super::Tick(DeltaTime);
	

	if (CurDistance > MaxMidZoomDistanceLevel) {
		if (RotationToReach != MaxZoomRotation) {
			RotationToReach = MaxZoomRotation;
			CameraRoot->AttachToComponent(SpringArmMax, FAttachmentTransformRules::KeepRelativeTransform);
			CurSpringArm = SpringArmMax;
			CurMinSpringArmLength = MinSpringArmMaxLength;
			CurMaxSpringArmLength = MaxSpringArmMaxLength;
			
		}
	}
	else {
		if (CurDistance > MidMinZoomDistanceLevel && CurDistance < MaxMidZoomDistanceLevel) {
			if (RotationToReach != MidZoomRotation) {
				RotationToReach = MidZoomRotation;
				CameraRoot->AttachToComponent(SpringArmMid, FAttachmentTransformRules::KeepRelativeTransform);
				CurSpringArm = SpringArmMid;
				CurMinSpringArmLength = MinSpringArmMidLength;
				CurMaxSpringArmLength = MaxSpringArmMidLength;
				
				
			}
		}
		else {
			if (CurDistance < MidMinZoomDistanceLevel) {
				if (RotationToReach != MinZoomRotation) {
					RotationToReach = MinZoomRotation;
					CameraRoot->AttachToComponent(SpringArmMin, FAttachmentTransformRules::KeepRelativeTransform);
					CurSpringArm = SpringArmMin;
					CurMinSpringArmLength = MinSpringArmMinLength;
					CurMaxSpringArmLength = MaxSpringArmMinLength;
					
					
				}
			}
		}
	}

	if (CameraInMovement) {
		LengthToAdd = (LengthToReach - CurSpringArm->TargetArmLength) * DeltaTime * MoveSpeed;
		if (FMath::Abs(LengthToAdd) > PositionningPrecision) {
			CurSpringArm->TargetArmLength += LengthToAdd;
		}
		else {
			CameraInMovement = false;
		}
		CurDistance = CurSpringArm->TargetArmLength;
	}

	
	float AngleXToAdd = 0, AngleYToAdd = 0;
	float MousePosX, MousePosY;
	
	if (!isDraging && Planet && PlayerController) {
		int32 ViewportX, ViewportY;

		//FVector CurOrbitY = -InitialForwardVector * FVector::Distance(PlanetLocation, GetActorLocation());
		FVector AxisToRotate = FVector::ZeroVector;


		PlayerController->GetMousePosition(MousePosX, MousePosY);
		PlayerController->GetViewportSize(ViewportX, ViewportY);

		float CurFactorX = MousePosX / ViewportX;
		if (CurFactorX > MaxFactorX && CurFactorX < 0.9999) {
			AngleXToAdd = -PlanetRotationSpeed * DeltaTime;

		}
		else {
			if (CurFactorX < MinFactorX && CurFactorX > 0.0001) {
				AngleXToAdd = PlanetRotationSpeed * DeltaTime;
			}
		}

		float CurFactorY = MousePosY / ViewportY;
		if (CurFactorY > MaxFactorY && CurFactorY < 0.9999) {

			AngleYToAdd = -PlanetRotationSpeed * DeltaTime;
		}
		else {
			if (CurFactorY < MinFactorY && CurFactorY >0.0001) {
				AngleYToAdd = PlanetRotationSpeed * DeltaTime;

			}
		}
	}
	
	MoveCameraAlongOrbit(AngleXToAdd, AngleYToAdd);
}

// Called to bind functionality to input
void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCamera::MoveCamera(float value)
{
	LengthToReach = FMath::Clamp(CurSpringArm->TargetArmLength + value * MoveStrength, MinZoomDistanceFromPlanet, MaxZoomDistanceFromPlanet);
	CameraInMovement = true;
}

void APlayerCamera::MoveCameraAlongOrbit(float valueX, float valueY)
{
	FVector PlanetLocation = Planet->GetActorLocation();
	FVector CurOrbit = -GetActorForwardVector() * FVector::Distance(PlanetLocation, GetActorLocation());
	if (valueX != 0 || valueY != 0) {
		float nextPitch = GetActorRotation().Pitch - valueY;
		if (nextPitch > MaxRotationPitch || nextPitch < MinRotationPitch) valueY = 0;

		CurOrbit = CurOrbit.RotateAngleAxis(valueY, GetActorRightVector());
		CurOrbit = CurOrbit.RotateAngleAxis(valueX, GetActorUpVector());

		SetActorLocation(PlanetLocation + CurOrbit);

		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlanetLocation));
	}
}

