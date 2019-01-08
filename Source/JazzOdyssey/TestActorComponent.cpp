// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActorComponent.h"

// To give us access to GetTimeSeconds()
#include "Engine/World.h"

// Access to debug tools
#include "Engine.h"


// Sets default values for this component's properties
UTestActorComponent::UTestActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTestActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTestActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float BeatCount = GetWorld()->GetTimeSeconds() - BeatCountOld;
	FString CurrentTimeString = FString::SanitizeFloat(GetWorld()->GetTimeSeconds());

	if (BeatCount >= BeatFrequency)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time is %s"), *CurrentTimeString);
		BeatCountOld = GetWorld()->GetTimeSeconds();
	}

	// ...
}
