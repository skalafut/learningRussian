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
    move up one directory and into the bin directory
    ./LanguageGame.exe

