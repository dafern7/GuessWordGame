/*this is the console executable, that makes use of the BullCow class
this acts as the view in a MVC pattern and is responsible for all user
interaction for game logic see FBullCowGame class*/
#pragma once
#include "stdafx.h" //importing a file
#include <iostream> //importing standard stuff
#include <string>   //imports string operator <<
#include "FBullCowGame.h" //import our own header file

using int32 = int; 
using FText = std::string;
//prototypes
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText  getValidGuess();
bool AsktoPlayAgain(); 

//global access to BCGame
FBullCowGame BCGame; //instantiate a new game- need a CONSTRUCTOR (the initialization values)

//the entry point for our application 
int main() {
	bool bPlayAgain = false; //initialize boolean
	do {
	PrintIntro();
	PlayGame();
	PrintGameSummary();
	bPlayAgain = AsktoPlayAgain();
	} 
	while (bPlayAgain);

	return 0; //exit application
}

void PlayGame()
{
	BCGame.Reset();
	//loop for the number of guess tries while the game is NOT won
	// and there are still trys remaining

	int32 MaxTries = BCGame.GetMaxTries();

	 while (!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries) {     //! means negation (changed for to while)

		FText Guess = getValidGuess(); 
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "Cows = " << BullCowCount.Cows; 
		std::cout << std::endl;
	 }
	 return;
}

 //introduce the game
void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n"; //cout is an overloaded operator needs <<
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? \n";
	std::cout << "You have " << BCGame.GetMaxTries() << " attempts at this!\n";
}

//get the guess from the user (error checking)
FText getValidGuess() {
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText Guess = "";  //define a place for "Guess" (initialize)
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << std::endl;
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:;
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EWordStatus::Not_Isogram:;
			std::cout << "Please enter an isogram.\n";
			break;
		case EWordStatus::Not_Lowercase:;
			std::cout << "Please enter a lowercase word.\n";
			break;
		default:
			//assume guess valid
			break;
		}
	} while (Status != EWordStatus::OK); //keep looping until we get valid input (no errors)
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.isGameWon() == true) {
		std::cout << "You have won!\n";
	}
	else {
		std::cout << "Try Again :(\n";
	}
}

bool AsktoPlayAgain()
{
	std::cout << "Do you want to play again with the same word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y'); //single quote y
}
