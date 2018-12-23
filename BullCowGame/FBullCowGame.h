#pragma once

#include <string>

// Alias typing
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

	// Makes the game be in a fresh state
	void Reset();
	
	// Counts Bulls & Cows, and increases try # assuming valid guess
	FBullCowCount SubmitGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};