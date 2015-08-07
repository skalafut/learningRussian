#include <LanguageGame.h>
#include <string>
#include <iostream>
#include <stdio.h>

#define DEBUG

using namespace std;

int main(){

	///tell the game where to find the input word list and output score tracker files
	LanguageGame newGame("/home/user1/kalafut/languagePractice/learningRussian/data/englishToRussianList.txt","/home/user1/kalafut/languagePractice/learningRussian/data/gameScoreHistory.txt");

#ifdef DEBUG
	cout<<"made an instance of LanguageGame class"<<endl;
#endif

	newGame.setupGame();
	return 0;

}
