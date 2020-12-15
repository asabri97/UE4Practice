// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    InitGame();
}
 
void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
  
    else 
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::InitGame()
{
    PrintLine(TEXT("Welcome to Bull Cows"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("press enter to continue..."));  
}

void UBullCowCartridge::EndGame()
{
    bGameOver = false;
    PrintLine(TEXT("Press enter to play again."));
    InitGame();
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("yOU HAVE WON"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Sorry you have %i lives remaining. \nTry again."), Lives);
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        return;
    }

    // Check if isogram. Prompt to Guess again. Check right number of characters
    if (!IsIsogram(Guess))
    {
        PrintLine(("No repeating words, guess again"));
        return;
    }

    // Remove Life
    PrintLine(TEXT("You lost a life"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You lost. \nNo lives remaining"));
        PrintLine(TEXT("The hidden word was, %s"), *HiddenWord);
        EndGame();
        return;
    }

    // Show the player Bulls and Cows
    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Sorry you have %i lives remaining. \nTry again."), Lives);

}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 Index = 0;
    int32 Comparison = Index + 1;
    
    for (Index; Index < Word.Len(); Index++)
    {
        for (Comparison; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
                ValidWords.Emplace(Word);    
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }  
        }   
    }
    return Count;
}