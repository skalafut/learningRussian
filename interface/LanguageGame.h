#include <map>
#include <vector>
#include <utility>
#include <string>

using namespace std;

class LanguageGame{
	public:
		///link a file containing words and phrases in two languages to the class member var _wordListFile
		///pathToInputFile and pathToScoreHistoryFile must be absolute path names!
		///_scoreHistoryFile lists performance data from prior sessions of the game
		LanguageGame(string pathToInputFile, string pathToScoreHistoryFile):
			_wordListFile(pathToInputFile),
			_scoreHistoryFile(pathToScoreHistoryFile){};

		///fill the private member var _mapBtwnLanguages with words and phrases from _wordListFile, and set initial values for the numbers used in score keeping
		void setupGame();

		///initialize the integers and strings used for tracking game performance
		void initializePerformanceMetrics(){
			_numTested = 0;
			_numCorrect = 0;
			_numHintsOnCorrectTranslations = 0;
			_numHintsOnIncorrectTranslations = 0;
			_dateAndTime = "DATE  TIME";
			_gameMode = "MODE";
			_numNewAdditions = 0;
			_numReviewed = 0;
		};

		///insert mode allows words and phrases to be added to _wordList.
		///the word or phrase in both languages must be provided in the correct order, and separated by a colon
		void insertMode();


		///test the player's vocabulary
		void testMode();


		///review words and phrases which have been saved to the word and phrase bank
		void reviewMode();


		///coming in the future!  The computer randomly picks adjectives, nouns, and verbs from
		///the word bank, and constructs a sentence.  The user (a native speaker) then tells
		///the computer if this sentence is sensible or nonsense.  The computer will use machine
		///learning to develop its own intuition of how to develop logical sentences.
		void nativeSpeakerInsertMode();

		///start a new game session.  The player will pick the mode at the beginning - insert, test, review, or native speaker.
		///First version of test mode will print one word or phrase to the screen, and ask for
		///the translation.  Each incorrect answer will result in a hint printed to the screen.
		///The hint will be of the form "the word or phrase begins with: firstChar".
		///after three incorrect guesses, the correct translation will be printed to the screen,
		///and the game will move on to another word or phrase.
		void runGame();

		///methods to update int and string private member vars
		///recordDateAndTime() and recordGameMode() will be called once per game
		///the other increment and update fxns will be called many times per game
		void recordDateAndTime(string currentDateAndTime);
		void updateHintsOnCorrectTranslations(int hintsOnOneCorrectWord);
		void updateHintsOnIncorrectTranslations(int hintsOnOneIncorrectWord);
		void incrementNumTested();
		void incrementNumCorrect();
		void incrementNumReviewed();
		void incrementNumNewAdditions();
		void recordGameMode(string mode);
		void addIndexToIndexesAlreadyShownVector(int key);
		
		///check if the word or phrase tied to _mapBtwnLanguages[val] has already been shown
		///return true if it has been shown
		bool hasAlreadyBeenShown(int val);

	private:
		string _wordListFile;	///< path to the txt file which holds pairs of words and phrases in two languages 
		
		///key for map is an int representing the order in which the word or phrase pair was read in
		///the value for the map is a pair which links the a word or phrase which has been translated into two languages 
		map<int, pair<string,string> > _mapBtwnLanguages;
		
		
		///when a new game starts this vector will have no elements in it
		///if the game is run in test or review mode, then this vector will keep track of the words and phrases from _mapBtwnLanguages
		///which have been shown
		///at the end of every game in review or test mode this vector will be emptied
		vector<int> _indexesAlreadyShown;
		
		/**
		 * _scoreHistoryFile shows how well I performed in prior sessions of the game
		 * each line in _scoreHistoryFile lists the date and time (US Central time) when the game session began,
		 * the number of words and phrases which were tested, the number of correctly translated words/phrases,
		 * the number of hints used on words/phrases which were correctly translated, and the number of hints used
		 * on words/phrases which were not translated correctly 
		 *
		 * a perfect game session, where all words/phrases which were tested were translated correctly with a few
		 * hints, would result in this entry in _scoreHistoryFile:
		 *
		 * 08/10/15      13:30  test      0             0        30      30         5                  0
		 * date          time   mode   #reviewed    #added    #tested  #correct  #hintsCorrect  #hintsIncorrect
		 */
		string _scoreHistoryFile;
		
		///the following integer and string variables are reset to zero at the beginning of every new game, and are written to _scoreHistoryFile
		///at the end of every game
		int _numTested;	///< number of words and phrases tested in one game running in test mode
		int _numCorrect;	///< number of words and phrases which were correctly translated in one game running in test mode
		int _numHintsOnCorrectTranslations;	///< number of hints used on words and phrases which were correctly translated in one game running in test mode
		int _numHintsOnIncorrectTranslations;	///< number of hints used on words and phrases which were incorrectly translated in one game running in test mode
		int _numNewAdditions;	///< number of new words and phrases added in one game running in insert mode
		int _numReviewed;	///< number of words and phrases which were reviewed in one game running in review mode
		string _dateAndTime;
		string _gameMode;	///< the mode of the game, like insert, test, review, or native speaker


};///end class LanguageGame
