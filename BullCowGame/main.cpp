/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
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
void PrintGameSummary();
bool AskToPlayAgain();

// Initialize
FBullCowGame BCGame;

// the entry point for our application
int main() {
	do {
		PrintIntro();
		PlayGame(); // TODO: Allow for player to pick a letter length
	} while (AskToPlayAgain());

	return 0; // exit the application with zero status code
}

void PrintIntro() {
	// introduce the game
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Welcome to Bulls and Cows, a challenging word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?";
	std::cout << std::endl << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { // loop as long as there are turns left and the game isn't won
		FText Guess = GetValidGuess();
		FBullCowCount BullCow = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCow.Bull << ". Cows = " << BullCow.Cow << std::endl  << std::endl;
	}

	PrintGameSummary(); // prints a summary
	return;
}

// loop continually until player inputs valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		std::cout << "Guess # " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: "; // get a guess from the player
		std::getline(std::cin, Guess);

		Status = BCGame.IsGuessValid(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters" << std::endl << std::endl;
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

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Good Job - You won!" << std::endl;
	} else {
		std::cout << "Looks like you ran out of tries! Better luck next time!" << std::endl;
	}

	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
