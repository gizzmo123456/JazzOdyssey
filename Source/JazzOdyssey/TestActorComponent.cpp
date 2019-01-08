// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActorComponent.h"

// To give us access to GetTimeSeconds()
#include "Engine/World.h"

// Access to debug tools
#include "Engine.h"

// To give us input functionality so we can press buttons to do stuff in-game.
#include "Components/InputComponent.h"


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

	SetupInputComponent();

	// ...
	
}

void UTestActorComponent::SetupInputComponent()
{
	/// Look for attached InputComponent (only appears at run time!)
	InputComponentPointer = GetOwner()->FindComponentByClass<UInputComponent>();

	/// If found, we will bind all necessary actions (like Grab and Release) here.
	if (InputComponentPointer)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found for %s."), *GetOwner()->GetName());

		// Bind the Grabber input action. 
		/* FName ActionName ("Grab") must be spelled exactly the same as in the Unreal input panel.
		/// IE_Pressed is when button is pressed. There is also IE_Released.
		/// "this" is the 'object' this is operating on, it is a reference to Grabber itself.
		/// notice how the reference to (the address of) UGrabber::Grab() has omitted the parentheses.
		/// To summarize: Action Name, when button is Pressed, reference Grabber, look for the Grab function. */
		InputComponentPointer->BindAction("Red", IE_Pressed, this, &UTestActorComponent::HitRed);
		InputComponentPointer->BindAction("Blue", IE_Released, this, &UTestActorComponent::HitBlue);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent not found for %s. You may be unable to hit left and right."), *GetOwner()->GetName());
	}
}

void UTestActorComponent::HitRed()
{
	// UE_LOG(LogTemp, Warning, TEXT("Pressed RED."));

	bRedHit = true;
}

void UTestActorComponent::HitBlue()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed BLUE."));

	bBlueHit = true;
}

// Called every frame
void UTestActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float beatCount = GetWorld()->GetTimeSeconds() - beatCountOld;
	FString currentTimeString = FString::SanitizeFloat(GetWorld()->GetTimeSeconds());

	if (beatCount >= beatFrequency)
	{
		if (barCount == 3)
		{
			// UE_LOG(LogTemp, Warning, TEXT("TICK. Time is %s"), *currentTimeString);
			beatCountOld = GetWorld()->GetTimeSeconds();
			barCount = 0;
		}
		else
		{
			// UE_LOG(LogTemp, Warning, TEXT("TOCK. Time is %s"), *currentTimeString);
			beatCountOld = GetWorld()->GetTimeSeconds();
			barCount++;

			UE_LOG(LogTemp, Warning, TEXT("HIT RED!"));
			if (bRedHit)
			{
				UE_LOG(LogTemp, Log, TEXT("NICE!"));
				bRedHit = false;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("FAILURE!"));
			}
		}
	}

	// ...
}