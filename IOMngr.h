#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

/*
* sourceName -> input file
* listingName -> output file to be created (or stdout if NULL)
*/
int openFiles(char *sourceName, char *listingName);

/*
* close sourceFile & listingFile (if created)
*/
void closeFiles();

/*
* Get and return next source character
* echo lines in source file to listing file (and number lines)
* return EOF at end of source file
*/
char getNextSourceChar();

/*
* Write a line containing a single '^' in the indicated column
* if there is no listing file then the current
* line should be echoed to stdout the first
* time (for that line) that writeIndicator or
* writeMessage is called.
*/
void writeIndicator(int column);

/*
* Write message on new line
*/
void writeMessage(char *message);

int getCurrentLineNum();
int getCurrentColumnNum();