#include <iostream>
#include <stdlib.h>

// Global Gameplay Variables //
int Code1;
int Code2;
int Code3;
int CodeSum;
int CodeProduct;

// initialize random seed
void InitRandomNumberSeed()
{
    srand(time(NULL));
}

// get random number between 1 and range
int GetRandomNumber(int Range=10)
{
    return rand() % Range + 1;
}

int Sum(int Num1, int Num2, int Num3)
{
    return Num1 + Num2 + Num3;
}

int Product(int Num1, int Num2, int Num3)
{
    return Num1 * Num2 * Num3;
}

void InitGlobalGameplayVars()
{
    Code1 = GetRandomNumber();
    Code2 = GetRandomNumber();
    Code3 = GetRandomNumber();

    CodeSum = Sum(Code1, Code2, Code3);
    CodeProduct = Product(Code1, Code2, Code3);
}

void PrintStartingMessage()
{
    std::cout << "You are a secret agent breaking into a secure server room...\n";
    std::cout << "Enter the correct code to continue...";
}

void PrintClosingMessage(bool PlayerWon)
{
    // Closing Message
    if (PlayerWon)
    {
        std::cout << "\nYou cracked the code!";
    }
    else
    {
        std::cout << "\nYou ran out of guesses! Better luck next time!";
    }
    std::cout << "\nThe correct numbers were " << Code1 << " " << Code2 << " " << Code3 << std::endl;
}

// handles one round of player guessing gameplay
bool GetPlayerGuesses()
{
    // Get guesses from player
    int Guess1, Guess2, Guess3;
    std::cout << "What are the three numbers? ";
    std::cin >> Guess1 >> Guess2 >> Guess3;
    /*
        * Encountered a weird bug here. If you enter a letter instead of a number, the
        * remaining numbers entered will be used in the next loop. It doesn't appear
        * that cin.clear & cin.ignore are fully clearing the buffer here. The bug seems
        * to only affect the very next loop, but can still cause you to lose the game 
        * even if you enter the correct digits, since it substitutes in your previous
        * guess(es).
        * Might be interesting to investigate to see if there's a proper way to clear
        * out the input buffer. Easiest solution, however, would probably be to do some
        * proper input validation and only allow integers to pass, otherwise require the
        * player to reenter their guesses.
        */
    std::cin.clear(); // Clears any errors
    std::cin.ignore(); // Discards the buffer

    // Helpful feedback to player about their guesses
    std::cout << std::endl;
    std::cout << "-- Your Guesses --" << std::endl;
    std::cout << "You guessed: " << Guess1 << " " << Guess2 << " " << Guess3 << std::endl;
    std::cout << "Sum: " << Sum(Guess1, Guess2, Guess3) << std::endl;
    std::cout << "Product: " << Product(Guess1, Guess2, Guess3) << std::endl;
    std::cout << "------------------" << std::endl;

    // Check if guesses are right and exit loop, or loop again if wrong
    if (CodeSum == Sum(Guess1, Guess2, Guess3) && CodeProduct == Product(Guess1, Guess2, Guess3))
    {
        return true; // Successful guess
    }
    return false; // Failed to guess
}

void PlayGame()
{
    PrintStartingMessage();

    int TimesGuessed = 1;
    int MaxGuesses = 3;
    bool GuessedCorrectly = false;
    do {
        // Initial Message
        std::cout << std::endl;
        std::cout << "There are 3 numbers in the code\n";
        std::cout << "The sum of the numbers is " << CodeSum << std::endl;
        std::cout << "The product of the numbers is " << CodeProduct << std::endl;
        std::cout << std::endl;
        std::cout << " --- Guess " << TimesGuessed << " of " << MaxGuesses << " ---\n";

        GuessedCorrectly = GetPlayerGuesses();
        TimesGuessed++;

        if (GuessedCorrectly) break;

        // Incorrect Guess Message (skip on final loop)
        if (TimesGuessed <= MaxGuesses)
        {
            std::cout << std::endl;
            std::cout << "That doesn't seem right... Try again!\n";
            std::cout << "---------------------------------------------------";
            std::cout << std::endl;
        }

    } while (TimesGuessed <= MaxGuesses);

    PrintClosingMessage(GuessedCorrectly);
}

int main(int argc, char* argv[])
{
    InitRandomNumberSeed();
    InitGlobalGameplayVars();
    PlayGame();

    return 0;
}