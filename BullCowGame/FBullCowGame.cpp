
#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map // Alias typing to make syntac UE4 friendly

using int32 = int; // Alias typing to make syntac UE4 friendly

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset() {
	bGameIsWon = false;
	MyCurrentTry = 1;

	const FString HIDDEN_WORD = "judge"; // Must be an isogram
	MyHiddenWord = HIDDEN_WORD;
	return;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,3}, {4,6}, {5,6}, {6,8}, {7,10}, {8, 10}, {9,10},{10,10} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
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

	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowercase(Guess)) { 
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) {
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
	MyCurrentTry++;
	
	FBullCowCount BullCowCount;
	// assuming both guess and hidden word are the same length
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) { // loop through all letters the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) { // compare letters against guess
			if (Guess[GChar] == MyHiddenWord[MHWChar]) { // if they match then
				if (MHWChar == GChar) {  // and if they in the same place
					BullCowCount.Bull++;
				} else {
					BullCowCount.Cow++;
				}
			}
		}
	}

	// Check if the game is won
	if (BullCowCount.Bull == WordLength) { bGameIsWon = true; }

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
	// Default to true
	bool bIsogram = true;

	// Treat 0 and 1 letter words are isograms
	if (Guess.length() <= 1) { return bIsogram;  }

	TMap<char, bool> LetterSeen; // Set up a map
	for (auto Letter : Guess) { // loop through all letters of the Guess
		Letter = tolower(Letter);
			
		if (LetterSeen[Letter]) { // Not an isogram
			bIsogram = false;
			break;
		} else {
			LetterSeen[Letter] = true;
		}
	}

	return bIsogram;
}

bool FBullCowGame::IsLowercase(FString Guess) const {
	bool bIsLower = true;

	// Treat 0 and 1 letter words as lower
	if (Guess.length() <= 1) { return bIsLower; }

	for (auto Letter : Guess) { // loop through all the letters in the guess
		if (!islower(Letter)) { // not lower then set to not lower and break out of loop
			bIsLower = false;
			break;
		}
	}

	return bIsLower;
}
