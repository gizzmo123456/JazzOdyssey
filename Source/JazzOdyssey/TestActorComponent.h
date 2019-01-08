// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JAZZODYSSEY_API UTestActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTestActorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// protected is the same as private, except protected stuff is accessible by everything that inherits from this
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	// 
	UInputComponent* InputComponentPointer = nullptr;
	void SetupInputComponent();

	void HitRed();
	void HitBlue();
	bool bRedHit = false;
	bool bBlueHit = false;

	UPROPERTY(EditAnywhere)
		float beatFrequency = 0.5f;

	float beatCountOld = 0.0f;
	int32 barCount = 3;

	// An array
	TArray<float> audioTimeline;
};
