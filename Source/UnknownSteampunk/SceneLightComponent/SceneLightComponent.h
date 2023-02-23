// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/SpotLightComponent.h"
//#include "Components/ConeComponent.h"
#include "SceneLightComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNSTEAMPUNK_API USceneLightComponent : public USpotLightComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USceneLightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category="Swith")
	bool State = true;
	UPROPERTY(EditAnywhere, Category="Swith")
	float SwitchDelay = 0.1f;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable, Category="Switch")
	virtual void ToggleActiveState();
	UFUNCTION(BlueprintCallable, Category="Delay")
	void SetDelay(float delay);
	UFUNCTION(BlueprintCallable, Category="Delay")
	float GetDelay();
		
};