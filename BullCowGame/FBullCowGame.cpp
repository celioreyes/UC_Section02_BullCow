#include "FBullCowGame.h"
#include <iostream>
// Alias typing
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() {
	Reset();
}

int32 FBullCowGame::GetMaxTries() const {
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const {
	return bGameIsWon;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}


EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const {

	if (false) { // if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	} else if (false) { // if guess is not all lowercase
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) { // if guess is not correct legnth
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
	
	// If something goes wrong and non of the conditionals are hit
	// just return an error to ensure we gracefully shut down
	return EGuessStatus::Unknown_Error;
}

// Receives valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {

	// increment the turn
	MyCurrentTry++;
	// setup return value
	FBullCowCount BullCowCount;
	
	// assuming both guess and hidden word are the same length
	int32 WordLength = MyHiddenWord.length();
	// loop through all letters the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {	
		// compare letters against guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// and if they in the same place
				if (MHWChar == GChar) {
					// inc the bull count
					BullCowCount.Bull++;
				} else {
					// inc the cow count
					BullCowCount.Cow++;
				}
			}
		}
	}

	// Check if the game is won
	if (BullCowCount.Bull == WordLength) { bGameIsWon = true; }

	return BullCowCount;
}

void FBullCowGame::Reset() {
	bGameIsWon = false;
	MyCurrentTry = 1;

	constexpr int MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "run";
	MyHiddenWord = HIDDEN_WORD;
	return;
}
