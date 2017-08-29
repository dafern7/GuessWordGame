#pragma once
#include <string>
//DO NOT USE USING NAMESPACE
using int32 = int;
using FString = std::string;

struct FBullCowCount {
	int32 Bulls = 0; //struct contains two integers	
	int32 Cows = 0;
};

enum class EWordStatus { //enum class is stronger than enum, can have repeated values in different enums using this
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public: 
	FBullCowGame(); //constructor
	//some methods that may be used in the class
	void Reset(); 

	int32 GetMaxTries() const ;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString HiddenWord() const;

	bool isGameWon() const;

	EWordStatus CheckGuessValidity(FString) const; 
	FBullCowCount SubmitValidGuess(FString); 

private: //try not to focus on this, only use by class
	//see constructor for initialization
	int32 MyCurrentTry ;
	int32 MyMaxTries;
	FString MyHiddenWord; 
	bool bGameIsWon;
	bool IsIsogram(FString Word) const;
	bool IsLowercase(FString Word) const ;
};