// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
// include capsule component
#include "Components/CapsuleComponent.h"

#include "PickupAndRotateActor.generated.h"
class AUnknownSteampunkCharacter;
UCLASS()
class UNKNOWNSTEAMPUNK_API APickupAndRotateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupAndRotateActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComp;
	UPROPERTY(EditAnywhere, Category = "Box Component")
	class UBoxComponent* MyComp;
	
	void RotateActor();
	void Pickup();

	bool bHolding;
	bool bGravity;
	UPROPERTY(EditAnywhere, Category = "Offset")
	float DeltaZ = 5;

	FRotator ControlRotation;
	AUnknownSteampunkCharacter* MyCharacter;
	UCapsuleComponent* PlayerCapsule;
	FVector ForwardVector;
	FVector LastLocation;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};

