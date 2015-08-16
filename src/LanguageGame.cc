#include <LanguageGame.h>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <random>

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
		_wordsInLanguageOne.push_back(phraseInLanguageOne);
		_wordsInLanguageTwo.push_back(phraseInLanguageTwo);
		
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
		incrementNumNewAdditions();

		///ask the user if they want to add another word
		cout<<"do you want to add another word or phrase? (y/n):\t";
		string response;
		cin >> response;
		if(response.find('y') != string::npos) addAnotherWord = true;

	}while(addAnotherWord);

	cout<<"leaving insert mode"<<endl;
	writeToWordList.close();

}///end insertMode()


///print out a word or phrase in both languages, then ask the user
///if they want to see another word or phrase
void LanguageGame::reviewMode(){

}///end reviewMode()

void LanguageGame::testMode(){

}///end testMode()


void LanguageGame::nativeSpeakerMode(){

}///end nativeSpeakerMode()


void LanguageGame::recordDateAndTime(string currentDateAndTime){
	_dateAndTime = currentDateAndTime;
}

void LanguageGame::updateHintsOnCorrectTranslations(int hintsOnOneCorrectWord){
	_numHintsOnCorrectTranslations += hintsOnOneCorrectWord;
}

void LanguageGame::updateHintsOnIncorrectTranslations(int hintsOnOneIncorrectWord){
	_numHintsOnIncorrectTranslations += hintsOnOneIncorrectWord;
}

void LanguageGame::incrementNumTested(){_numTested++;}

void LanguageGame::incrementNumCorrect(){_numCorrect++;}

void LanguageGame::incrementNumReviewed(){_numReviewed++;}

void LanguageGame::incrementNumNewAdditions(){_numNewAdditions++;}

void LanguageGame::recordGameMode(string mode){_gameMode = mode;}



void LanguageGame::runGame(){
	///open a file stream to the txt file which tracks how often the game is played, the number of correct translations, etc
	ofstream scoreKeeper(_scoreHistoryFile.c_str(),ofstream::app);
	
	///compute the date and time (US central zone) when the game begins, and save it to the class variable _dateAndTime 
	time_t rawTime;
	time(&rawTime);	///< this isn't a constructor! calling this fills rawTime with useful information.
	struct tm * timeInfo = localtime(&rawTime);
	string startDateAndTime(asctime(timeInfo));
	recordDateAndTime(startDateAndTime);

	string selectedMode;
	bool knownMode = true;	///< indicates if user input mode does not match one of the known modes
	
	do{
		cout<<"what game mode would you like to run?"<<endl;
		cout<<"type r for review mode, and review existing words and phrases in the word bank without being tested"<<endl;
		cout<<"type t for test mode, and put your vocabulary to the test!"<<endl;
		cout<<"type i for insert mode, and add new words and phrases to the word bank"<<endl;
		cout<<"type ns for native speaker mode, and teach the computer how to combine existing words in the word bank into sensible sentences.  For native speakers only!"<<endl;

		cin >> selectedMode;
		if(selectedMode.find('r')==string::npos && selectedMode.find('i')==string::npos && selectedMode.find('t')==string::npos && selectedMode.find("ns")==string::npos ) knownMode = false;
		if(!knownMode) cout<<"the game mode you entered is not recognized!"<<endl;

	}while(!knownMode);

	///now that a game mode has been selected, run the game!
	recordGameMode(selectedMode);
	if(selectedMode=="r") reviewMode();
	if(selectedMode=="i") insertMode();
	if(selectedMode=="t") testMode();
	if(selectedMode=="ns") nativeSpeakerMode();


	scoreKeeper <<_dateAndTime<<"    "<<_gameMode <<"    "<<_numReviewed <<"    "<<_numNewAdditions <<"    "<<_numTested<<"    "<<_numCorrect<<"    "<<_numHintsOnCorrectTranslations<<"    "<<_numHintsOnIncorrectTranslations<<endl;

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


