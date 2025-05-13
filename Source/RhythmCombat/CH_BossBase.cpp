// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_BossBase.h"

// Sets default values
ACH_BossBase::ACH_BossBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BossSongTimeSignature = EQuartzTimeSignatureQuantization::QuarterNote;
	hasTimeToAttack = false;
}

// Called when the game starts or when spawned
void ACH_BossBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACH_BossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACH_BossBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACH_BossBase::UseCustomAttackStruct(int CustomIndex)
{
	if (CustomAttackNotesList.IsValidIndex(CustomIndex))
	{
		FCustomAttackNotes usedAttackStruct = CustomAttackNotesList[CustomIndex];

		tempCustomNotes = usedAttackStruct.NotesInCustomAttack;

		tempCustomAttackMontages = usedAttackStruct.MontagesWithCustomNotes;

		CheckIfNextAttackInArrayExists();

		/*for (EQuartzCommandQuantization tempNote : tempCustomNote)
		{
			float tempAttackLength = CalculateCustomAttackLength(BossSongBPM, tempNote, BossSongTimeSignature);

			UseCustomAttack(usedAttackStruct.MontagesWithCustomNotes[CustomIndex], tempAttackLength);
			
		}*/
	}
}

bool ACH_BossBase::CheckIfNextAttackInArrayExists()
{
	if (tempCustomNotes.IsValidIndex(currentCustomMoveIndex))
	{
		if (tempCustomAttackMontages.IsValidIndex(currentCustomMoveIndex)) {
			EQuartzCommandQuantization tempCustomNote = tempCustomNotes[currentCustomMoveIndex];
			UAnimMontage* tempCustomAttackMontage = tempCustomAttackMontages[currentCustomMoveIndex];

			float tempAttackLength = CalculateCustomAttackLength(BossSongBPM, tempCustomNote, BossSongTimeSignature);
			float tempMontageLength = tempCustomAttackMontage->CalculateSequenceLength();
			float tempMontageSpeedMult = tempMontageLength / tempAttackLength;
			UseCustomAttack(tempCustomAttackMontage, tempMontageSpeedMult);

			currentCustomMoveIndex++;
			return true;
		}
	}
	currentCustomMoveIndex = 0;
	return false;
}

void ACH_BossBase::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	CheckIfNextAttackInArrayExists();
}

float ACH_BossBase::DealDamageToBoss(float DamageToDeal)
{
	bossHealth -= DamageToDeal;

	return bossHealth;
}


void ACH_BossBase::UseCustomAttack(UAnimMontage* AnimToPlay, float SpeedMult)
{
	this->GetMesh()->GetAnimInstance()->Montage_Play(AnimToPlay, SpeedMult);

	FOnMontageEnded EndDelegate;

	EndDelegate.BindUObject(this, &ACH_BossBase::OnAnimationEnded);

	this->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate);

	//this->GetMesh()->GetAnimInstance()->OnMontageEnded.AddUnique(OnAnimationEnded);
}

float ACH_BossBase::CalculateCustomAttackLength(float SongBPM, EQuartzCommandQuantization NoteType, EQuartzTimeSignatureQuantization TimeSignature)
{
	float tempTimeSigMult;
	
	float tempNoteValueMult = 60.0f;

	float tempDesiredAttackLength;

	/*Sets the time signature multiplier based on the time sig speed // I'M AN IDIOT I DIDN'T NEED THIS I DON'T THINK*/
	switch (TimeSignature)
	{
		case EQuartzTimeSignatureQuantization::HalfNote:
			tempTimeSigMult = 2.0f;
			break;

		case EQuartzTimeSignatureQuantization::QuarterNote:
			tempTimeSigMult = 4.0f;
			break;

		case EQuartzTimeSignatureQuantization::EighthNote:
			tempTimeSigMult = 8.0f;
			break;
		case EQuartzTimeSignatureQuantization::SixteenthNote:
			tempTimeSigMult = 16.0f;
			break;
		case EQuartzTimeSignatureQuantization::ThirtySecondNote:
			tempTimeSigMult = 32.0f;
	}
	/*Sets the note value multiplier based on the custom note's value*/
	switch (NoteType)
	{
		case EQuartzCommandQuantization::ThirtySecondNote:
			tempNoteValueMult = 7.5f;
			break;
		case EQuartzCommandQuantization::SixteenthNote:
			tempNoteValueMult = 15.0f;
			break;
		case EQuartzCommandQuantization::EighthNote:
			tempNoteValueMult = 30.0f;
			break;
		case EQuartzCommandQuantization::QuarterNote:
			tempNoteValueMult = 60.0f;
			break;
		case EQuartzCommandQuantization::HalfNote:
			tempNoteValueMult = 120.0f;
			break;
		case EQuartzCommandQuantization::WholeNote:
			tempNoteValueMult = 240.0f;
			break;
		case EQuartzCommandQuantization::DottedSixteenthNote:
			tempNoteValueMult = 22.5f;
			break;
		case EQuartzCommandQuantization::DottedEighthNote:
			tempNoteValueMult = 45.0f;
			break;
		case EQuartzCommandQuantization::DottedQuarterNote:
			tempNoteValueMult = 90.0f;
			break;
		case EQuartzCommandQuantization::DottedHalfNote:
			tempNoteValueMult = 120.0f;
			break;
		case EQuartzCommandQuantization::DottedWholeNote:
			tempNoteValueMult = 360.0f;
			break;
		case EQuartzCommandQuantization::SixteenthNoteTriplet:
			tempNoteValueMult = 10.0f;
			break;
		case EQuartzCommandQuantization::EighthNoteTriplet:
			tempNoteValueMult = 20.0f;
			break;
		case EQuartzCommandQuantization::QuarterNoteTriplet:
			tempNoteValueMult = 40.0f;
	}

	tempDesiredAttackLength = tempNoteValueMult / SongBPM;
	return tempDesiredAttackLength; 
}

