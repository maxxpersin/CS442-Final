#include "SymTab.h"

SymTab *createSymTab(int size)
{
    /*
    * Init table
    */
    SymTab *table = malloc(sizeof(SymTab));

    table->size = size;                                         // Assign size
    table->contents = malloc(sizeof(SymEntry *) * table->size); // Init contents list
    int i;
    for (i = 0; i < table->size; i++)
    {
        table->contents[i] = NULL;
    }

    table->current = NULL; // HEAD is null
    return table;
}

void destroySymTab(SymTab *table)
{
    SymEntry *currList = NULL;
    SymEntry *currListEntry = NULL;
    SymEntry *temp = NULL;
    int i;

    for (i = 0; i < table->size; i++)
    {
        currList = table->contents[i];
        temp = currList;
        while (temp)
        {
            currListEntry = temp->next;
            free(temp->name);
            free(temp);
            temp = currListEntry;
        }
    }

    /*
    * Sanity Check
    */
    free(currListEntry);
    free(temp);
    free(table->contents);
    free(table);
}

int enterName(SymTab *table, char *name)
{
    // Check if name in symbol table
    int i;
    SymEntry *curr;
    SymEntry *prev = NULL;

    if (findName(table, name) == 0)
    {
        // Not in table, add
        int hash = generateHash(table->size, name);

        SymEntry *newEntry = malloc(sizeof(SymEntry));
        newEntry->name = (char *)malloc(sizeof(char) * strlen(name));
        newEntry->name = strdup(name);
        newEntry->attribute = NULL;

        newEntry->next = table->contents[hash];
        table->contents[hash] = newEntry;

        table->current = newEntry;

        return 1;
    }
    else
    {
        return 0;
    }
}

int findName(SymTab *table, char *name)
{
    SymEntry *curr;
    int hash = generateHash(table->size, name);

    curr = table->contents[hash];

    while (curr)
    {
        if (strcmp(curr->name, name) == 0)
        {
            table->current = curr;
            return 1;
        }

        curr = curr->next;
    }

    return 0;
}

int hasCurrent(SymTab *table)
{
    return table->current ? 1 : 0;
}

void setCurrentAttr(SymTab *table, void *attr)
{
    table->current->attribute = attr;
}

void *getCurrentAttr(SymTab *table)
{
    return table->current->attribute;
}

char *getCurrentName(SymTab *table)
{
    return table->current->name;
}

int startIterator(SymTab *table)
{
    int i;
    for (i = 0; i < table->size; i++)
    {

        if (table->contents[i])
        {
            table->current = table->contents[i];
            return 1;
        }
    }

    return 0;
}

int nextEntry(SymTab *table)
{
    //Check if at end of hash table
    if (!table->current)
    {
        return 0;
    }

    int hash = generateHash(table->size, table->current->name);
    if (hash == table->size - 1)
    {
        SymEntry *curr = table->contents[hash];
        SymEntry *prev = NULL;
        while (curr)
        {
            prev = curr;
            curr = curr->next;
        }

        if (prev && strcmp(prev->name, table->current->name) == 0)
        {
            return 0;
        }
    }

    if (table->current->next)
    {
        table->current = table->current->next;
    }
    else
    {
        hash++;
        while (!table->contents[hash])
        {
            hash++;
            if (hash >= table->size)
            {
                return 0;
            }
        }
        table->current = table->contents[hash];
    }

    return 1;
}

int generateHash(int size, char *name)
{
    int hash = 0, i;

    for (i = 0; i < strlen(name); i++)
    {
        hash += name[i];
    }

    hash %= size;

    if (hash < 0)
    {
        hash += size;
    }

    return hash;
}