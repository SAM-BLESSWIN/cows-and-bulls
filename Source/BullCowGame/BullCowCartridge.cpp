// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    Score=0;
    CheckValidWords();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ProcessGame(Input);
}

void UBullCowCartridge::SetupGame()
{
    Lives=10;
    HiddenWord=ValidWords[FMath::RandRange(0,ValidWords.Num()-1)];
   // PrintLine(FString::Printf(TEXT(" %s "),*HiddenWord));
    bGameover=false;

    PrintLine(TEXT("Welcome to Cow and Bull game"));
    PrintLine(FString::Printf(TEXT("Guess the %i letter word"),HiddenWord.Len()));
    PrintLine(TEXT("Lives: %i"),Lives);
    PrintLine(TEXT("press TAB to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameover=true;
    PrintLine(TEXT("Press ENTER to PlayAgain..."));
}

void UBullCowCartridge::ProcessGame(const FString& Guessword) 
{
    if(bGameover)
    {
        ClearScreen();
        SetupGame();
        return;
    }

    //correct guess
    if(Guessword==HiddenWord)
    {
        Score++;
        PrintLine(TEXT("Winner :)"));
        PrintLine(TEXT("WinningStreak: %i"),Score);
        EndGame();
        return;
    }

    //length not equal
    if(Guessword.Len()!=HiddenWord.Len())
    {
        PrintLine(FString::Printf(TEXT("Enter a %i letter word"),HiddenWord.Len()));
        PrintLine(TEXT("Lives: %i"),Lives);
        return;
    }

    //check isogram
    if(!IsIsogram(Guessword))
    {
        PrintLine(TEXT("The guessed word contains repeated letters"));
        return;
    }

    //word mismatch
    --Lives;
    if(Lives>0)
    {
        CheckCowsandBulls(Guessword,HiddenWord);
        PrintLine(TEXT("Try again,remainingLives: %i"),Lives);
    }
    else
    {
        ClearScreen();
        PrintLine(TEXT("You have lost the game :("));
        PrintLine(FString::Printf(TEXT("The hidden word : %s"),*HiddenWord));
        PrintLine(TEXT("WinningStreak: %i"),Score);
        EndGame();
    }

}

bool UBullCowCartridge::IsIsogram(const FString& Guessword) const
{
    int32 hashmap[26];
    for(int32 i=0;i<26;i++)
    {
        hashmap[i]=0;
    }

    int32 l=Guessword.Len();
    for(int32 i=0;i<l;i++)
    {
        hashmap[Guessword[i]-'a']++;

        if(hashmap[Guessword[i]-'a']>1)
        {
            return false;
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::CheckValidWords()
{
    for(FString w:Words)
    {
        if(IsIsogram(w))
        {
            ValidWords.Emplace(w);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::CheckCowsandBulls(const FString& GuessWord ,const FString& HiddenWord) 
{
    Bulls=0;
    Cows=0;
    for (int32 i = 0; i < GuessWord.Len(); i++)
    {
       for(int32 j=0;j<GuessWord.Len();j++)
       {
           if(GuessWord[i]==HiddenWord[j])
            {
                if(i==j)
                {
                    Bulls++;
                    break;
                }
                else
                {
                    Cows++;
                    break;
                }
                
            }
       }
    }
    PrintLine(TEXT("Bulls: %i, Cows: %i"),Bulls,Cows);
}