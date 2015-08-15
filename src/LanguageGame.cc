#include <LanguageGame.h>
#include <map>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

//#define DEBUG
//#define DEBUG2

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

	inputListStrm.close();

#ifdef DEBUG
	for(map<string,string>::const_iterator phraseIt=_mapBtwnLanguages.begin(); phraseIt!=_mapBtwnLanguages.end(); phraseIt++){
		cout<<"the key \t"<< phraseIt->first<<"\t is tied to the value \t"<< phraseIt->second<<"\t in _mapBtwnLanguages"<<endl;
	}///end loop over _mapBtwnLanguages elements
#endif

}///end setupGame()

void LanguageGame::insertMode(){
	ofstream writeToWordList(_wordListFile.c_str(),ofstream::app);	///< open file in append mode
	bool addAnotherWord = false;
	do{
		cout<<"enter a word or phrase in English, a colon without leading or trailing whitespace, and the translation into Russian"<<endl;
		string newAddition;
		cin >> newAddition;
		while(newAddition.find(":") == string::npos){
			newAddition.clear();
			cout<<"enter the new word or phrase with a colon separating the two translations"<<endl;
			cin >> newAddition;
		}

		///now write the string to _wordListFile
		writeToWordList << newAddition << endl;

		///ask the user if they want to add another word
		cout<<"do you want to add another word or phrase? (y/n):\t";
		string response;
		cin >> response;
		if(response.find('y') != string::npos) addAnotherWord = true;

	}while(addAnotherWord);

	cout<<"leaving insert mode"<<endl;
	writeToWordList.close();

}///end insertMode()

void LanguageGame::setDateAndTime(string newDateAndTime){
	_dateAndTime = newDateAndTime;
}

void LanguageGame::updateHintsOnCorrectTranslations(int hintsOnOneCorrectWord){
	_numHintsOnCorrectTranslations += hintsOnOneCorrectWord
}

void LanguageGame::updateHintsOnIncorrectTranslations(int hintsOnOneIncorrectWord){
	_numHintsOnIncorrectTranslations += hintsOnOneIncorrectWord
}

void LanguageGame::incrementNumTested(){_numTested++}

void LanguageGame::incrementNumCorrect(){_numCorrect++}


void LanguageGame::runGame(){
	///open a file stream to the txt file which tracks how often the game is played, the number of correct translations, etc
	ofstream scoreKeeper(_scoreHistoryFile.c_str(),ofstream::app);
	
	///compute the date and time (US central zone) when the game begins, and save it to the class variable _dateAndTime 
	time_t rawTime;
	time(&rawTime);	///< this isn't a constructor! calling this fills rawTime with useful information.
	struct tm * timeInfo = localTime(&rawTime);
	string startDateAndTime(asctime(timeInfo));
	setDateAndTime(startDateAndTime);

	scoreKeeper <<_dateAndTime<<"    "<<_numTested<<"    "<<_numCorrect<<"    "<<_numHintsOnCorrectTranslations<<"    "<<_numHintsOnIncorrectTranslations<<endl;

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


