#include <LanguageGame.h>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <chrono>	///used for RNG seed
#include <random>

//#define DEBUG
//#define DEBUG2
//#define DEBUG3

using namespace std;

///this fxn randomly choses 1 or 2 and returns the value as an integer
int LanguageGame::randomOneOrTwo(){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine randNumGenerator(seed);	///< without this the seed would be the same every time the game is run - bad!!
	uniform_int_distribution<int> uniformDistribution(1,100);
	int randomNum = uniformDistribution(randNumGenerator);
	int valToReturn;
	if( remainder(randomNum, 2) == 0 ) valToReturn = 1;
	else valToReturn = 2;
#ifdef DEBUG3
	cout<<"randomly generated "<< randomNum <<endl;
	cout<<"show language number "<< valToReturn <<endl;
#endif
	return valToReturn;
}///end randomOneOrTwo()


///print a phrase which should be translated, ask for the player to type in the translation,
///and check to see if the translation is correct.  Continue this process until the translation
///is correct, or three hints have been used
///
///mapIndex = the integer key used for _mapBtwnLanguages
///just before leaving testOnePhrase() the bool successful and int hintsUsed should be updated
///with nHints and correctTranslation
///if doOfficeMode is true, then only ask the player to translate phrases from the foreign
///language into their native language
void LanguageGame::testOnePhrase(int & hintsUsed, int mapIndex, bool & successful,bool doOfficeMode){
	int nHints = 0;	///<local variable, set hintsUsed equal to this just before leaving testOnePhrase()
	bool done = false;	///<local var, set successful equal to this just before leaving testOnePhrase()
	string wordToTranslate, playerInput, correctWordTranslation;
	int showThisLanguage = randomOneOrTwo();
	if(doOfficeMode) showThisLanguage = 2;
	if(showThisLanguage==1){
		wordToTranslate = _mapBtwnLanguages[mapIndex].first;
		correctWordTranslation = _mapBtwnLanguages[mapIndex].second;
	}
	else{
		///show a phrase from language two, then ask for the translation into language one
		wordToTranslate = _mapBtwnLanguages[mapIndex].second;
		correctWordTranslation = _mapBtwnLanguages[mapIndex].first;
	}///end else

	///print out a phrase, and ask for the translation
	cout<< "translate this:\t" << wordToTranslate << endl;
	cin >> playerInput;
	
	if(playerInput.compare(correctWordTranslation) == 0){
		cout<<"good work!"<<endl;
		done = true;
	}///end if(correct translation with zero hints)

	///if the word was not translated correctly the first time, give up to three characters from
	///correctWordTranslation as hints to the player
	else{
		while(!done && nHints < 3){
			playerInput.clear();
			nHints++;	///<increment nHints for every loop iteration
			cout<<"letter number "<< nHints<<" of the translation is\t"<< correctWordTranslation.at(nHints-1) <<endl;
			cout<<"translate this:\t"<<  wordToTranslate <<endl;
			cin >> playerInput;
			if(playerInput.compare(correctWordTranslation) == 0){
				cout<<"good work!"<<endl;
				done = true;
			}
		}///end while(hints are needed)
	}///end else(the word/phrase was not translated correctly the first time, without any hints)
	if(done==false && nHints==3) cout<<"the correct translation is:\t"<< correctWordTranslation <<endl;

	///update the vars which were passed by reference to testOnePhrase()
	hintsUsed = nHints;
	successful = done;
}///end testOnePhrase()


///this method is designed to ask a question, receive y/n input, and update a bool variable
void askToContinue(bool & keepGoing, string outputStatement){
	cout << outputStatement;
	string response;
	cin >> response;
	if(response.find('y') != string::npos) keepGoing = true;
	else keepGoing = false;

}///end askToContinue()

void LanguageGame::setupGame(){
	ifstream inputListStrm(_wordListFile.c_str());

#ifdef DEBUG
	cout<<"setup ifstream to _wordListFile"<<endl;
#endif

	int pairNumber = -1;	///< used as the key for _mapBtwnLanguages
	while(inputListStrm.peek() != EOF && inputListStrm.good() ){
		pairNumber++;
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

		_mapBtwnLanguages[pairNumber] = make_pair(phraseInLanguageOne,phraseInLanguageTwo);
	}///end while()

	inputListStrm.close();

#ifdef DEBUG
	for(map<int, pair<string,string> >::const_iterator phraseIt=_mapBtwnLanguages.begin(); phraseIt!=_mapBtwnLanguages.end(); phraseIt++){
		cout<<"the phrase \t"<< (phraseIt->second).first <<"\t is linked to the phrase \t"<< (phraseIt->second).second <<"\t in _mapBtwnLanguages"<<endl;
	}///end loop over _mapBtwnLanguages elements
#endif

}///end setupGame()

void LanguageGame::insertMode(){
	ofstream writeToWordList(_wordListFile.c_str(),ofstream::app);	///< open file in append mode
	bool addAnotherWord = false;
	do{
		cout<<"enter a word or phrase in English, followed by a colon without leading or trailing whitespace, and the translation into Russian"<<endl;
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
		askToContinue(addAnotherWord,"do you want to add another word or phrase? (y/n):\t");

	}while(addAnotherWord);

	cout<<"leaving insert mode"<<endl;
	writeToWordList.close();

}///end insertMode()


///print out a word or phrase in both languages, then ask the user
///if they want to see another word or phrase
void LanguageGame::reviewMode(){
	int wordIndex;
	bool keepReviewing = false;

	do{
		wordIndex = findNewRandomElement();
		///now we have a key for _mapBtwnLanguages which has not been used
		cout<< (_mapBtwnLanguages[wordIndex]).first <<" == "<< (_mapBtwnLanguages[wordIndex]).second <<endl;
		cout<<"  "<<endl;
		incrementNumReviewed();
		addIndexToIndexesAlreadyShownVector(wordIndex);
		if(_indexesAlreadyShown.size() == _mapBtwnLanguages.size() ){
			std::cout<<"you cycled through all of the words and phrases in englishToRussianList.txt !  Good work!  Add more words or phrases to this file."<<std::endl;
			break;
		}
		askToContinue(keepReviewing,"do you want to continue reviewing? (y/n):\t");
		cout<<"  "<<endl;
	
	}while(keepReviewing);

	cout<<"leaving review mode"<<endl;

}///end reviewMode()

void LanguageGame::testMode(bool doOfficeMode){
	bool keepTesting = false;
	int wordIndex, languageIndex;	///<languageIndex chooses which language to show to the player

	do{
		int numHintsUsed = 0;
		bool correct = false;
		wordIndex = findNewRandomElement();
		testOnePhrase(numHintsUsed,wordIndex,correct,doOfficeMode);	///<runs the test on one phrase

		if(correct){
			incrementNumCorrect();
			updateHintsOnCorrectTranslations(numHintsUsed);
		}
		else updateHintsOnIncorrectTranslations(numHintsUsed);
		
		addIndexToIndexesAlreadyShownVector(wordIndex);
		incrementNumTested();
		if(_indexesAlreadyShown.size() == _mapBtwnLanguages.size() ){
			std::cout<<"you cycled through all of the words and phrases in englishToRussianList.txt !  Good work!  Add more words or phrases to this file."<<std::endl;
			break;
		}
		askToContinue(keepTesting,"do you want to continue testing your vocabulary? (y/n):\t");
	}while(keepTesting);

}///end testMode()


void LanguageGame::nativeSpeakerInsertMode(){

}///end nativeSpeakerInsertMode()


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

void LanguageGame::addIndexToIndexesAlreadyShownVector(int key){
	_indexesAlreadyShown.push_back(key);
}

bool LanguageGame::hasAlreadyBeenShown(int val){
	for(unsigned int i=0; i<_indexesAlreadyShown.size() ;i++){
		if(_indexesAlreadyShown[i] == val) return true;
	}
	return false;
}

	
int LanguageGame::findNewRandomElement(){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine randNumGenerator(seed);
	uniform_int_distribution<int> uniformIntDistribution(0,_mapBtwnLanguages.size()-1);
	int newElement = uniformIntDistribution(randNumGenerator);

	if(hasAlreadyBeenShown(newElement)){
		while(hasAlreadyBeenShown(newElement)){
			newElement = uniformIntDistribution(randNumGenerator);
		}///end while(newElement has already been used)
	}///end if(newElement has already been used)

#ifdef DEBUG3
	cout<<"there are "<< _mapBtwnLanguages.size() <<" elements in _mapBtwnLanguages"<<endl;
	cout<<"the randomly chosen element is "<< newElement<<endl;
#endif

	return newElement;

}///end findNewRandomElement()

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
		cout<<"type ns for native speaker insert mode, and teach the computer how to combine existing words in the word bank into sensible sentences, then add these words into the word bank.  For native speakers only!"<<endl;
		cout<<"type o for office mode, and test your translation skills going from a foreign language to your native language"<<endl;

		cin >> selectedMode;
		if(selectedMode.find('r')==string::npos && selectedMode.find('i')==string::npos && selectedMode.find('t')==string::npos && selectedMode.find("ns")==string::npos && selectedMode.find('o')==string::npos ) knownMode = false;
		if(!knownMode) cout<<"the game mode you entered is not recognized!"<<endl;

	}while(!knownMode);

	///now that a game mode has been selected, run the game!
	recordGameMode(selectedMode);
	if(selectedMode=="r") reviewMode();
	if(selectedMode=="i") insertMode();
	if(selectedMode=="t") testMode(false);
	if(selectedMode=="o") testMode(true);
	if(selectedMode=="ns") nativeSpeakerInsertMode();


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


