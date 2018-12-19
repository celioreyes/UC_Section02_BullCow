#include <iostream>
#include <string>

void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();

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
	constexpr int WORLD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a challenging word game." << std::endl;
	std::cout << "Can you guess the " << WORLD_LENGTH << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

void PlayGame() {
	// loop for the number of turns asking for guesses
	constexpr int NUM_OF_TURNS = 5;
	for (int count = 1; count <= NUM_OF_TURNS; count++) {
		std::cout << "Your guess was: " << GetGuess() << std::endl;
		std::cout << std::endl;
	}
}

std::string GetGuess() {
	// get a guess from the player
	std::cout << "Enter your guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	std::string Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
