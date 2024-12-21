#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void clearScreen() {
    // Simple way to clear the console screen
    cout << string(100, '\n');
}

void waitForKeyPress() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void playGame() {
    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    // Generate random number between 1 and 100
    int randomNumber = rand() % 100 + 1;
    int userGuess = 0;
    int attempts = 0;
    const int maxAttempts = 10;

    clearScreen();
    cout << "=====================================" << endl;
    cout << "       Welcome to the Number Guessing Game!" << endl;
    cout << "=====================================" << endl;
    cout << "Instructions:" << endl;
    cout << "1. I have selected a random number between 1 and 100." << endl;
    cout << "2. You have up to " << maxAttempts << " attempts to guess the correct number." << endl;
    cout << "3. After each guess, I will tell you if your guess is too high or too low." << endl;
    cout << "4. Try to guess the number in the fewest attempts possible." << endl;
    cout << "=====================================" << endl;

    while (attempts < maxAttempts) {
        cout << "\nAttempt " << attempts + 1 << " of " << maxAttempts << ": Enter your guess: ";
        cin >> userGuess;

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 100." << endl;
            continue;
        }

        attempts++;

        if (userGuess < randomNumber) {
            cout << "Your guess is too low. Try again!" << endl;
        } else if (userGuess > randomNumber) {
            cout << "Your guess is too high. Try again!" << endl;
        } else {
            cout << "Congratulations! You guessed the correct number: " << randomNumber << endl;
            cout << "It took you " << attempts << " attempts to guess the number." << endl;
            break;
        }
    }

    if (attempts == maxAttempts && userGuess != randomNumber) {
        cout << "\nYou've used all your attempts. The correct number was: " << randomNumber << endl;
    }
}

int main() {
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        playGame();
        cout << "\nWould you like to play again? (y/n): ";
        cin >> playAgain;

        if (playAgain == 'y' || playAgain == 'Y') {
            clearScreen();
        }
    }

    cout << "\nThank you for playing the Number Guessing Game. Goodbye!" << endl;
    return 0;
}

