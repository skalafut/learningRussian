#include <LanguageGame.h>
#include <string>
#include <iostream>
#include <stdio.h>

//#define DEBUG

using namespace std;

int main(){

	///tell the game where to find the input word list and output score tracker files
	string localWordList = "../data/englishToRussianList.txt";
	string localScoreHistory = "../data/gameScoreHistory.txt";
	LanguageGame newGame(localWordList,localScoreHistory);

#ifdef DEBUG
	cout<<"made an instance of LanguageGame class"<<endl;
#endif

	newGame.setupGame();

#ifdef DEBUG
	cout<<"called setupGame()"<<endl;
#endif

	newGame.initializePerformanceMetrics();
	newGame.runGame();
#ifdef DEBUG
	cout<<"called runGame()"<<endl;
#endif

	return 0;

}
