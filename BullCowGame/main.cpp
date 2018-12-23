/*
	This is the console executable, that makes use of the FBullCowGame class
*/
#include <iostream>
#include <string>

// Include local classes
#include "FBullCowGame.h"

// Alias typing
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

// Initialize
FBullCowGame BCGame;

// the entry point for our application
int main() {
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // exit the application with zero status code
}

void PrintIntro() {
	// introduce the game
	std::cout << "Welcome to Bulls and Cows, a challenging word game." << std::endl;
	std::cout << "Can you guess the " <<BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop as long as there are turns left and the game isn't won
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCow = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCow.Bull;
		std::cout << ". Cows = " << BullCow.Cow;

		std::cout << std::endl;
	}

	// TODO - Add a game summary at the end
}

// loop continually until player inputs valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		// get a guess from the player
		std::cout << "Attempt #" << BCGame.GetCurrentTry() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.IsGuessValid(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Please provide a word with no repeating letters" << std::endl << std::endl;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word in all lowercase" << std::endl << std::endl;
			break;
		case EGuessStatus::Unknown_Error:
			std::cout << "Unkown Error occured with program. Exiting..." << std::endl << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until player inputs a valid word

	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
