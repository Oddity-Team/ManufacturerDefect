// Fill out your copyright notice in the Description page of Project Settings.


#include "../PickupAndRotateActor/PickupAndRotateActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnknownSteampunk/UnknownSteampunkCharacter.h"
#include "Components/BoxComponent.h"
// Sets default values
APickupAndRotateActor::APickupAndRotateActor()
{
	
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//MyComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// MyComp->SetSimulatePhysics(true);
	// MyComp->SetNotifyRigidBodyCollision(true);
    //    
	// MyComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	//MyComp->OnComponentHit.AddDynamic(this, &APickupAndRotateActor::OnCompHit);
	
	// Set as root component
	//RootComponent = MyComp;

	bHolding = false;
	bGravity = true;
	//add Cylinder to root
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	MyMesh->SetSimulatePhysics(true);
	MyMesh->SetNotifyRigidBodyCollision(true);
    MyMesh->SetupAttachment(RootComponent);
 
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/StarterContent/Cylinder"));
 
	if (CylinderAsset.Succeeded())
    {
        MyMesh->SetStaticMesh(CylinderAsset.Object);
        MyMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        MyMesh->SetWorldScale3D(FVector(1.f));
	}
	MyMesh->SetConstraintMode(EDOFMode::Type::YZPlane);
	MyMesh->OnComponentHit.AddDynamic(this, &APickupAndRotateActor::OnCompHit);
	

}

// Called when the game starts or when spawned
void APickupAndRotateActor::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<AUnknownSteampunkCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerCapsule = MyCharacter->FindComponentByClass<UCapsuleComponent>();

	TArray<USceneComponent*> Components;
 
	MyCharacter->GetComponents(Components);

	if(Components.Num() > 0)
	{
		for (auto& Comp : Components)
		{
			if(Comp->GetName() == "HoldingComponent")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	}

}

// Called every frame
void APickupAndRotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bHolding && HoldingComp)
	{
		SetActorLocationAndRotation(FVector(HoldingComp->GetComponentLocation().X,HoldingComp->GetComponentLocation().Y,LastLocation.Z+DeltaZ),MyMesh->GetComponentRotation());
	}
}

void APickupAndRotateActor::RotateActor()
{
    
	ControlRotation = GetWorld()->GetFirstPlayerController()->GetControlRotation();
	SetActorRotation(FQuat(ControlRotation));
}

void APickupAndRotateActor::Pickup()
{
	bHolding = !bHolding;	
	bGravity = !bGravity;
	MyMesh->SetEnableGravity(bGravity);
	MyMesh->SetSimulatePhysics(true);
	
	MyMesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics/**/);//
	LastLocation = MyMesh->GetComponentLocation();
}

void APickupAndRotateActor::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
	if ((OtherActor != MyCharacter) &&(OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		//MyCharacter->ToggleItemPickup();
		if(bHolding && HoldingComp)
		{
			
				MyCharacter->ToggleItemPickup();
				

			
		}
	}
}