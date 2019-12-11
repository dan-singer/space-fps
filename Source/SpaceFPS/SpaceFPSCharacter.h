// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceFPSCharacter.generated.h"

class UInputComponent;

UENUM(BlueprintType)
enum class GunType : uint8 {
	Normal,
	Missile,
	NUM_GUNS
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCollectedPickup);

UCLASS(config=Game)
class ASpaceFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

	void Fire(UClass* ProjectileClass);

public:
	
	UFUNCTION(BlueprintCallable)
	void SetJumpEnabled(bool Value);

	UFUNCTION(BlueprintCallable)
	void SetCanFire(bool Value);

	UFUNCTION(BlueprintCallable)
	void CollectPickup();

	ASpaceFPSCharacter();

protected:

	UPROPERTY(BlueprintAssignable)
	FCollectedPickup CollectedPickup;

	FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
	int PickupsCollected = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool CanPlayerJump = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool CanFire = false;

	UPROPERTY(BlueprintReadOnly)
	bool Charging = false;

	UPROPERTY(EditDefaultsOnly)
	float MinChargeDuration = 1.0f;

	float LastFireTime = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	GunType Gun = GunType::Normal;

	int GunsUnlocked = 1;
	bool CanCharge = false;

	void OnJump();
	void OnEndJump();

	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASpaceFPSProjectile> NormalProjectile;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASpaceFPSProjectile> ChargeBeamProjectile;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASpaceFPSProjectile> MissileProjectile;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	UFUNCTION(BlueprintCallable)
	void ResetLocation();

	UFUNCTION(BlueprintCallable)
	void GiveChargeBeam();

	UFUNCTION(BlueprintCallable)
	void GiveNextWeapon();

protected:
	
	/** Fires a projectile. */
	void OnFire();

	void OnFireUp();

	void OnScrollUp();
	void OnScrollDown();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

