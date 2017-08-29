#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map> //import the map library
#define TMap std::map  //redefine std::map

using int32 = int;
FBullCowGame::FBullCowGame() {
	Reset(); //the constructor directly links to reset
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 4;
	const FString HIDDEN_WORD = "plane"; //see if we can change the hidden word!
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const //keep this value constant
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,2}, {4,3}, {5,4}, {6,5} };
	return WordLengthToMaxTries[MyHiddenWord.length()];  //passes hidden word length as the first int32
}														//then returns the second int32

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {   //if the guess isn't isogram,  
		return EWordStatus::Not_Isogram;    //return error
	}  
	else if (!IsLowercase(Guess)) {                       //if the game is not all lowercase, 
		return EWordStatus::Not_Lowercase;  //return error
	}  //TODO write method
	else if (Guess.length() != GetHiddenWordLength()) {     //if the guess length is wrong
		return EWordStatus::Wrong_Length;    //return error
	}
	else {
		return EWordStatus::OK;
	};
	
}

//recieves a valid guess/ increments try counter, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;  //set up a return variable
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	//loop through all letters in the hidden word
	for (int32 HiddenWChar = 0; HiddenWChar < WordLength; HiddenWChar++) {
		//compare letters against the guess
		for (int32 GWChar = 0; GWChar < WordLength; GWChar++) {
			if (Guess[GWChar] == MyHiddenWord[HiddenWChar]) {
				if (HiddenWChar == GWChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
				if (BullCowCount.Bulls == GetHiddenWordLength()) {
					bGameIsWon = true;
				}
				else {
					bGameIsWon = false;
				}
			}
		}
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
		return true;
	};
	//set up map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {	//for all letters of the word..
		Letter = tolower(Letter);  //store upper/lowercase letters
	//we do NOT have isogram
		if (LetterSeen[Letter]) {  //letter is already in the map
			return false;
		}
		else {
			LetterSeen[Letter] = true; //recording letter seen to the map
		}
	}
	return true; //for example if  /0 is entered (anything not letters)
}

bool FBullCowGame::IsLowercase(FString Word) const {
	if (Word.length() <= 0) {
		return true;
	}
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
		else {
			return true;
		}
	}
}
