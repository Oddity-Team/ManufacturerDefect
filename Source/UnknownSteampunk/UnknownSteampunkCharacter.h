// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickupAndRotateActor/PickupAndRotateActor.h"
#include "SceneLightComponent/SceneLightComponent.h"
#include "UnknownSteampunkCharacter.generated.h"

UCLASS(config=Game)
class AUnknownSteampunkCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	
	/** Holding Component */
	UPROPERTY(EditAnywhere)
	class USceneComponent* HoldingComponent;
	UPROPERTY(EditAnywhere)
    FVector HoldingRelativeLocation = FVector(0,0,0);
	virtual void Tick(float DeltaSeconds) override;

	

	/**Wall jump*/
	UPROPERTY(EditAnywhere, Category = "Jump")
	bool CanWallJump = 0;
	bool AxisMoving = 0;
	int TurnJump = 0;
	
	/**Soaring*/
	bool QKey = 0;
	UPROPERTY(EditAnywhere,Category = "Soaring")
	double Gravity{0.01};
	UPROPERTY(EditAnywhere,Category = "Soaring")
	bool bIsSoaring = 0;
	UPROPERTY(EditAnywhere,Category = "Soaring")
	double DefaultCharacterGravity{2};
	UPROPERTY(EditAnywhere,Category = "Soaring")
	double SoaringAcceleration{0};
	UPROPERTY(EditAnywhere,Category = "Soaring")
	double DefaultMaxAcceleration{0};
	UPROPERTY(EditAnywhere,Category = "Soaring")
	double SoaringVelocity{-20};
	//particle system
	UParticleSystem* UPart;
	UParticleSystem* UPartFire;
	UPROPERTY(EditAnywhere,Category = "Soaring")
	UParticleSystemComponent* LeftLegParticleSystem;
	UPROPERTY(EditAnywhere,Category = "Soaring")
	UParticleSystemComponent* RightLegParticleSystem;
	//UPROPERTY(EditAnywhere,Category = "Soaring")
	//UParticleSystemComponent* RightLegParticleSystem2;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* SoaringAudioBase;
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* SoaringAudioComponent;


	/**pickup and rotate*/
	UPROPERTY(EditAnywhere, Category = "Pickup")
	float FRadius = 200;
	UPROPERTY(EditAnywhere, Category = "Pickup")
	float FLength = 15;
	UPROPERTY(EditAnywhere, Category = "Pickup")
	bool bCanThrow;
	UPROPERTY(EditAnywhere, Category = "Pickup")
	bool bHoldingItem;
	bool bInspecting;
	UPROPERTY(EditAnywhere)
	class APickupAndRotateActor* CurrentItem;
	
	FVector HoldingComp;
	FRotator LastRotation;

	FVector Start;
	FVector ForwardVector;
	FVector End;
    float CharacterRotYaw;
	FHitResult Hit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;


	/**Light Component*/
	// UPROPERTY(EditAnywhere, Category ="Eye light")
	// USceneLightComponent* LeftEyeLightComponent;
	// UPROPERTY(EditAnywhere, Category ="Eye light")
	// USceneLightComponent* RightEyeLightComponent;
	
///
protected:

	/** Called for side to side input */
	void MoveRight(float Val);

    
    
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



public:
	AUnknownSteampunkCharacter();
    virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	// End of APawn interface
	void UpdateCharacter();
	void UpdatePickupAndRotate();
	void WallJump();
	void Jump();
	void ParticleToggle();
	UFUNCTION(BlueprintCallable, Category="Soaring")
	bool IsSoaring();
	void Soaring();
	UFUNCTION(BlueprintCallable, Category="Jump")
	bool IsWallJump();
	void SetWallJump(bool state);

	// pickup and rotate
	void ToggleItemPickup();
	void ToggleJumpParticles();
	void OnAction();
	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


};
