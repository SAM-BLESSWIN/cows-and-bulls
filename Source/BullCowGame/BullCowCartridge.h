// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame(); //user func to initialize values;
	void EndGame();
	void ProcessGame(const FString& Guessword);
	void CheckCowsandBulls(const FString& Guessword,const FString& HiddenWord);
	bool IsIsogram(const FString& Guessword)const;
	TArray<FString> CheckValidWords();

	// Your declarations go below!
	private:
		FString HiddenWord;
		int32 Score;
		int32 Lives;
		int32 Cows;
		int32 Bulls;
		bool bGameover;
		TArray<FString> ValidWords;
		TArray<FString> Words;
};
