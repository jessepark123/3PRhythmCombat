// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CH_BossBase.generated.h"

USTRUCT(BlueprintType)
struct FCustomAttackNotes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EQuartzCommandQuantization> NotesInCustomAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> MontagesWithCustomNotes;

	bool operator==(const FCustomAttackNotes& Other) const
	{
		if (NotesInCustomAttack != Other.NotesInCustomAttack)
		{
			return false;
		}
		return true;
	}
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<int> CustomAttackMontageStartupFrames;
};
UCLASS()
class RHYTHMCOMBAT_API ACH_BossBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACH_BossBase();

	// Tells the boss it is allowed to attack when this is true // DOESN'T MEAN THE BOSS WILL ATTACK, JUST SAYS IT CAN
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool hasTimeToAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCustomAttackNotes> CustomAttackNotesList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BossSongBPM = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EQuartzTimeSignatureQuantization BossSongTimeSignature;

	UPROPERTY()
	int currentCustomMoveIndex = 0;

	UPROPERTY()
	TArray<EQuartzCommandQuantization> tempCustomNotes;

	UPROPERTY()
	TArray<UAnimMontage*> tempCustomAttackMontages;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float bossHealth = 100.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Uses one of the Custom Attack Structs as laid out in the BP class*/
	UFUNCTION(BlueprintCallable)
	void UseCustomAttackStruct(int CustomIndex);

	
	/*Uses an attack, called from UseCustomAttackStruct*/
	UFUNCTION()
	void UseCustomAttack(UAnimMontage* AnimToPlay, float SpeedMult);

	/*Calculates the length of the attack based on the time signature, BPM, and type of note associated with the attack, called from UseCustomAttackStruct*/
	UFUNCTION()
	float CalculateCustomAttackLength(float SongBPM, EQuartzCommandQuantization NoteType, EQuartzTimeSignatureQuantization TimeSignature);

	UFUNCTION()
	bool CheckIfNextAttackInArrayExists();

	UFUNCTION()
	void OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	/*Finds all suitable custom attack structs indexes given an input of rhythm structs*/
	UFUNCTION(BlueprintCallable)
	TArray<int> FindSuitableAttacksForRhythm(TArray<EQuartzCommandQuantization> InAttackTimings);

	/*Does damage to the boss, is divded by 100 for UI bar later*/
	UFUNCTION(BlueprintCallable)
	float DealDamageToBoss(float DamageToDeal);
};
