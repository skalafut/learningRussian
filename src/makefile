#put this makefile inside the src directory

IDIR = ../interface
BUILDIR = ../bin
LIBDIR = ../lib
OBJDIR = obj

#additional libraries to use
LIBS=-lm

#define compiler type and compile time flags 
#original CC=g++ -std=c++0x
CC=g++ -std=c++11
CFLAGS=-I$(IDIR)


_OBJ = LanguageGame.o launchGame.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

#make a macro named DEPS which is a set of all .h files on which the .cc files depend
_DEPS = LanguageGame.h
#this call to patsubst puts $(IDIR)/ in front of all header files listed in _DEPS
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#define a rule which says all .o files depend on .cc files with the same name, and all
#header files in DEPS
#the line below the rule makes a .o file by compiling a .cc file with the compiler CC, and
#put the file output by this compilation in a .o file
# $@ and $< are special macros in makefiles
#$@ is linked to the left side of the : in the rule defined above
#$< is the first item in the dependencies list defined in the rule 
$(OBJDIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#by putting the object files in the dependency list (line below LanguageGame: ) and in the
#rule (LanguageGame: line), make knows to compile the .cc files individually, then
#build the executable
# $^ is a special macro in makefiles which is linked to the right side of the rule
$(BUILDIR)/LanguageGame.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BUILDIR)/*.exe


