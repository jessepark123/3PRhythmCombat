// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RhythmStructs.h"
#include "RhythmItem.generated.h"


UCLASS()
class RHYTHMCOMBAT_API ARhythmItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhythmItem();

	//struct values of the item
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FItemData ItemAttributes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
