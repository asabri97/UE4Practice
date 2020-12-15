// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    
    InitGame();
    
    PrintLine(TEXT("Number of possible word is %i: "), Words.Num());

    PrintLine(TEXT("Number of valid word is %i: "), GetValidWords(Words).Num());
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord);

    
    
}
 
void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
  
    else 
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
    PrintLine(TEXT("Welcome to Bull Cows"));

    HiddenWord = TEXT("cake");
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
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("yOU HAVE WON"));
        EndGame();
        return;
    }

    // Check if isogram. Prompt to Guess again. Check right number of characters
    if (!IsIsogram(Guess))
    {
        PrintLine(("No repeating words, guess again"));
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Sorry you have %i lives remaining. \nTry again."), Lives);
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
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

    PrintLine(TEXT("Sorry you have %i lives remaining. \nTry again."), Lives);

}

bool UBullCowCartridge::IsIsogram(FString Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;
    for (int32 Index = 0; Index < WordList.Num(); Index++)
    {
        if (WordList[Index].Len() >= 4 && WordList[Index].Len() <= 8 && IsIsogram(WordList[Index]))
        {
                ValidWords.Emplace(WordList[Index]);    
        }
    }
    return ValidWords;
}