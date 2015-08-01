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

};///end class LanguageGame