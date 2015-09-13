# learningRussian
This repository holds a game and tools developed to help anyone learn a new language.  These tools 
and game were originally developed for Russian, but they can be used with any language, 
given the appropriate input files.  The point of this game is to help memorize vocabulary and short
sentences which someone does not want to forget.  At the moment, this game cannot generate new words
or phrases by itself.

The data directory contains text files needed to run the game.  The file data/englishToItalianList.txt
contains a list of English words and phrases, and their translations into Italian.  To use the game
for another language, the only change is that a different txt file should be used instead of
englishToItalianList.txt.  In the txt file, the two translations must be separated by a colon, and
all white space characters between words on a single line must be replaced with underscores.
The file data/gameScoreHistory.txt keeps track of information pertinent to the user's performance
in all prior games, including when the games were played, the number of words tested, and the
number of words translated correctly.

The current game has 4 modes which are controlled through 3 methods defined in interface/LanguageGame.h.
The 3 methods, and other machinery to run the game, are implemented in src/LanguageGame.cc.
Insert mode allows the user to add words and phrases, plus their translations, into
data/englishToItalianList.txt.  Test mode, which can be run in normal mode or office mode, tests
the user's ability to translate words and phrases from one language into the other.  Office mode
tests the player's ability to translate words and phrases from the foreign language into the
player's native language.  Finally, review mode allows the player to review words already entered
into data/englishToItalianList.txt.

NOTE the player must add words and phrases into data/englishToItalianList.txt before running
the game in test or review mode for the first time.  As stated above, the current version of the
game cannot generate words or phrases on its own.  Future versions of this game will include this
feature!

INSTRUCTIONS TO DOWNLOAD AND PLAY THE GAME WITH ENGLISH AND ITALIAN
1. Install C++11 or newer, g++ version 4.6.3 or newer, and github software on your computer.
2. Run this command to download the learningRussian repository and the original development branch, named master.
   git clone https://github.com/skalafut/learningRussian.git

3. Run this command to checkout the branch for studying Italian and English.
   git checkout forKellyS 

4. Move to the learningRussian/src/ directory, and run the command 'make clean'.
5. Run the command 'make', and, if everything is compiled successfully, move up one directory
   and into the bin/ directory.
6. Run the executable file named LanguageGame.exe to launch the game.


REMINDERS
1. If you want to add improvements to this game please fork the entire learningRussian repository into your own github
   account, and make changes to the source code in the forked repository.
2. Use underscore characters instead of white space when adding an entry to data/englishToItalianList.txt which has
   more than one word. 
