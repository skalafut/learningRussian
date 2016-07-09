# learningRussian
This repository holds a game and tools developed to help me learn Russian vocabulary.  However, these tools 
and game can be used with any language, given the appropriate input files.

The data directory contains text files needed to run the game. The file data/englishToRussianList.txt contains a list of English words and phrases, and their translations into Russian. To use the game for another language, the only change is that a different txt file should be used instead of englishToRussianList.txt. The txt file must separate the two translations with a colon. The file data/gameScoreHistory.txt keeps track of information pertinent to the user's performance in all prior games, including when the games were played, the number of words tested, and the number of words translated correctly.

To download the game, first install github software on your computer. Then on a command line interface:

    git clone https://github.com/skalafut/learningRussian.git
    move into the learningRussian directory
    git branch yourGame
    git checkout yourGame
    move into the src directory
    type 'make clean' then hit enter
    type 'make' then hit enter to compile the game
    delete everything from the file data/gameScoreHistory.txt except the first line which has the column titles
    move up one directory and into the bin directory
    ./LanguageGame.exe

New words and phrases can be added to the game in two ways.  When using both methods, new words and phrases must be added in this format:
word:wordInOtherLanguage
phrase_one:phrase_one,_in_other_language_with_comma
else the game will not work.  The first method is to edit the txt file data/englishToRussianList.txt directly.  Editing this file is also the only way to remove or edit words and phrases currently used in the game.  The other method is by running the game through the instructions
shown above, and playing the game in "insert" mode by typing "i" when the game begins.  This way has the added advantage over directly editing
the word map file in that your additions to the game word and phrase list are tracked over time in the file data/gameScoreHistory.txt.

Feel free to add new features to this game in your branch, but NEVER execute this command in any branch:
git push origin master
or
git push -f origin master

