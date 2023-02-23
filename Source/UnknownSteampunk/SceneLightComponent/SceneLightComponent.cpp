// Fill out your copyright notice in the Description page of Project Settings.


#include "../SceneLightComponent/SceneLightComponent.h"

// Sets default values for this component's properties
USceneLightComponent::USceneLightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USceneLightComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,&USceneLightComponent::ToggleActiveState, SwitchDelay, false);
	// ...
	
}


// Called every frame
void USceneLightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void USceneLightComponent::ToggleActiveState()
{
	ToggleVisibility(State);
	State = !State;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,&USceneLightComponent::ToggleActiveState, SwitchDelay, false);
};

void USceneLightComponent::SetDelay(float delay)
{
	SwitchDelay = delay;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,&USceneLightComponent::ToggleActiveState, SwitchDelay, false);
};
float USceneLightComponent::GetDelay()
{
	return SwitchDelay;
};
