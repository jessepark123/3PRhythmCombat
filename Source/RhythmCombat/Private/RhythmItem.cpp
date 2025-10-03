// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmItem.h"

// Sets default values
ARhythmItem::ARhythmItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhythmItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhythmItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARhythmItem::UpdateItemAttributes()
{
	ItemAttributes.ItemDescription = ItemDescription;
	ItemAttributes.ItemName = ItemName;
	ItemAttributes.ItemNumber = ItemNumber;
	ItemAttributes.ItemClassRef = ARhythmItem::StaticClass();
}

