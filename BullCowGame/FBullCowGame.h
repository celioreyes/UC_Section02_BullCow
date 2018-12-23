/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once

#include <string>

// Alias typing to make syntac UE4 friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bull = 0;
	int32 Cow = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Unknown_Error
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus IsGuessValid(FString) const;

	void Reset(); // Makes the game be in a fresh state
	
	// Counts Bulls & Cows, and increases try # assuming valid guess
	FBullCowCount SubmitGuess(FString);
	// Print a game summary after the game is won or lost
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};