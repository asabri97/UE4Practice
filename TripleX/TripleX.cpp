#include <iostream>
#include <ctime>
using namespace std;

void PrintIntro(int Difficulty) {
     // Print starting message to the terminal
    cout << "\n\nEnter the correct code to level up to " << Difficulty;
    cout << "\n\n";
}

bool PlayGame(int Diffculty) {

   PrintIntro(Diffculty);

    const int CodeA = rand() % Diffculty + Diffculty;
    const int CodeB = rand() % Diffculty + Diffculty;
    const int CodeC = rand() % Diffculty + Diffculty;

    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;

    // Print CodeSum and CodeProduct to the terminal
    cout << "\n+ There are 3 numbers in the code";
    cout << "\n+ The codes add up to: " << CodeSum;
    cout << "\n+ The codes multiply to: " << CodeProduct << endl;

    // Store player guess
    int GuessA, GuessB, GuessC;
    cin >> GuessA >> GuessB >> GuessC;
   
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    // Check if the player has made the correct guess
    if (GuessSum == CodeSum && GuessProduct == CodeProduct) {
        cout << "You win!" << endl;
        return true;
    }
    else {
        cout << "Wrong numbers, Try again!" << endl;
        return false;
    }
}

int main() 
{
    srand(time(NULL));
    int LevelDifficulty = 1;
    int const MaxDifficulty = 5;

    while (LevelDifficulty <= MaxDifficulty) {
       bool bLevelComplete = PlayGame(LevelDifficulty);

        cin.clear(); // Clears any error
        cin.ignore(); // Discards the buffer

        if (bLevelComplete)
        {
            // increase the level difficulty
            ++LevelDifficulty;
        }  
    }

    cout << "\nGreat work! All levels completed!\n";
    return 0;
}