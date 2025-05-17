// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RhythmStructs.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName = "Default Name";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemDescription = "Default Description";
};

class RHYTHMCOMBAT_API RhythmStructs
{
public:
	RhythmStructs();
	~RhythmStructs();
};
