#include <map>
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
			_date = "DATE";
			_time = "TIME";
		};


		///insert mode allows words and phrases to be added to _wordList.
		///the word or phrase in both languages must be provided in the correct order, and separated by a colon
		void insertMode();


		///run the game.  First version will print one word or phrase to the screen, and ask for
		///the translation.  Each incorrect answer will result in a hint printed to the screen.
		///The hint will be of the form "the word or phrase begins with: firstChar".
		///after three incorrect guesses, the correct translation will be printed to the screen,
		///and the game will move on to another word or phrase.
		void runGame();

	private:
		string _wordListFile;	///< path to the txt file which holds pairs of words and phrases in two languages 
		map<string,string> _mapBtwnLanguages; 	///< key is a word or phrase in one language, value is the translation
		
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
		 * 08/10/15      13:30      30      30         5                  0
		 * date          time    #tested  #correct #hintsCorrect  #hintsIncorrect
		 */
		string _scoreHistoryFile;
		
		///the following integer and string variables are reset to zero at the beginning of every new game, and are written to _scoreHistoryFile
		///at the end of every game
		int _numTested;	///< number of words and phrases tested
		int _numCorrect;	///< number of words and phrases which were correctly translated
		int _numHintsOnCorrectTranslations;	///< number of hints used on words and phrases which were correctly translated
		int _numHintsOnIncorrectTranslations;	///< number of hints used on words and phrases which were incorrectly translated
		string _date, _time;


};///end class LanguageGame
