#include <LanguageGame.h>
#include <map>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

#define DEBUG
#define DEBUG2

using namespace std;

void LanguageGame::setupGame(){
	ifstream inputListStrm(_wordListFile.c_str());

#ifdef DEBUG
	cout<<"setup ifstream to _wordListFile"<<endl;
#endif

	while(inputListStrm.peek() != EOF && inputListStrm.good() ){
		if(inputListStrm.peek() == 35){
			///this line begins with a #, and should be skipped
			char discard[256];
			inputListStrm.getline(discard, 256, '\n');
			///once getLine() is called, the reader moves to the next line
#ifdef DEBUG
			cout<<"discarded a comment line"<<endl;
#endif
		}

		char phraseInBothLanguages[600];
		inputListStrm.getline(phraseInBothLanguages,600,'\n');

#ifdef DEBUG
		cout<<"read this line from the list of translated words and phrases"<<endl;
		cout<< phraseInBothLanguages << endl;
#endif

		string entireLine(phraseInBothLanguages);	///< convert phraseInBothLanguages to a string so string class methods can be used
		size_t colonPos = (entireLine.find_first_of(':')+1);
		string phraseInLanguageOne = entireLine.substr(0,colonPos-1);
		string phraseInLanguageTwo = entireLine.substr(colonPos);

#ifdef DEBUG
		cout<<"phraseInLanguageOne = \t"<< phraseInLanguageOne <<endl;
		cout<<"phraseInLanguageTwo = \t"<< phraseInLanguageTwo <<endl;
#endif

		_mapBtwnLanguages[phraseInLanguageOne] = phraseInLanguageTwo;
		
	}///end while()

#ifdef DEBUG
	for(map<string,string>::const_iterator phraseIt=_mapBtwnLanguages.begin(); phraseIt!=_mapBtwnLanguages.end(); phraseIt++){
		cout<<"the key \t"<< phraseIt->first<<"\t is tied to the value \t"<< phraseIt->second<<"\t in _mapBtwnLanguages"<<endl;
	}///end loop over _mapBtwnLanguages elements
#endif

}///end setupGame()

void LanguageGame::insertMode(){

}///end insertMode()

void LanguageGame::runGame(){
	ofstream scoreKeeper(_scoreHistoryFile.c_str(),ofstream::app);
	scoreKeeper <<_date<<"    "<<_time<<"    "<<_numTested<<"    "<<_numCorrect<<"    "<<_numHintsOnCorrectTranslations<<"    "<<_numHintsOnIncorrectTranslations<<endl;



	scoreKeeper.close();

#ifdef DEBUG2
	ifstream checkScoreFile(_scoreHistoryFile.c_str());
	while(checkScoreFile.peek() != EOF && checkScoreFile.good() ){
		char aLine[500];
		checkScoreFile.getline(aLine,500,'\n');
		cout << aLine << endl;
	}
#endif


}///end runGame()


