#include "IOMngr.h"

FILE *source;
FILE *source2;
FILE *listing;
char *_sourceName;
int currLine = 0;
int currColumn = 0;

int openFiles(char *sourceName, char *listingName)
{
    source = fopen(sourceName, "r");
    _sourceName = strdup(sourceName);

    if (source == NULL) // Opening source failed
    {
        return -1;
    }

    if (listingName)
    {
        listing = fopen(listingName, "w+");
        if (listing == NULL) // Opening listing failed
        {
            return 1;
        }
    }
    return 0;
}
void closeFiles()
{
    fclose(source);
    if (listing)
    {
        fclose(listing);
    }
}

char getNextSourceChar()
{
    char in = fgetc(source);
    if (in == '\n')
    {
        currColumn = 0;
        currLine++;
    }
    else
    {
        currColumn++;
    }

    return in;
}
void writeIndicator(int column)
{
    int i = 0;

    source2 = fopen(_sourceName, "r");
    char line[1028];
    while (i <= getCurrentLineNum())
    {
        fgets(line, 128, source2);
        i++;
    }

    i = 0;
    if (listing)
    {
        fputs(line, listing);
        while (i < column)
        {
            fputc(' ', listing);
            i++;
        }
        fputc('^', listing);
    }
    else
    {
        fprintf(stdout, "\n");
        while (i < column)
        {
            fprintf(stdout, " ");
            i++;
        }
        fprintf(stdout, "^");
    }
}
void writeMessage(char *message)
{
    if (listing)
    {
        fputs(message, listing);
        fputc('\n', listing);
    }
    else
    {
        fprintf(stdout, "%s\n", message);
    }
}
int getCurrentLineNum()
{
    return currLine;
}
int getCurrentColumnNum()
{
    return currColumn;
}