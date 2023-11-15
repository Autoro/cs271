/****************************************
 * C-ploration 9 for CS 271
 *
 * [NAME] Alex Miesbauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE];

/* Function: hash
* ---------------
* Generate the has value for the given string.
*
* str: The string to hash.
*
* return: The hash value of the given string.
*/
int hash(char* str)
{
    unsigned long hash = 5381;
    int character;

    while ((character = *str++))
    {
        hash = ((hash << 5) + hash) + character;
    }

    return (int)(hash % SYMBOL_TABLE_SIZE);
}

/* Function: symtable_find
* ------------------------
* Find the Symbol for the given key.
*
* key: The key to find in the hash array.
*
* returns: The Symbol associated with the given key if one exists, otherwise NULL.
*/
Symbol* symtable_find(char* key)
{
    int index = hash(key);
    while (hashArray[index] != NULL)
    {
        if (strcmp(hashArray[index]->name, key) == 0)
        {
            return hashArray[index];
        }

        index++;
        index %= SYMBOL_TABLE_SIZE;
    }

    return NULL;
}

/* Function: symtable_insert
* --------------------------
* Creates a Symbol for the given key and address, and inserts into the hash array.
*
* key: The name of the Symbol to be used as a key in the hash array.
* addr: The address of the Symbol.
*/
void symtable_insert(char* key, hack_addr addr)
{
    Symbol* item = (Symbol*)malloc(sizeof(Symbol));
    item->name = strdup(key);
    item->addr = addr;

    int index = hash(key);
    while (hashArray[index] != NULL && hashArray[index]->name != NULL)
    {
        index++;
        index %= SYMBOL_TABLE_SIZE;
    }

    hashArray[index] = item;
}

/* Function: symtable_display_table
* ---------------------------------
* Prints the current symbol table to the console.
*/
void symtable_display_table()
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        if (hashArray[i] != NULL)
        {
            printf(" (%s,%d)", hashArray[i]->name, hashArray[i]->addr);
        }
        else
        {
            printf(" ~~ ");
        }
    }

    printf("\n");
}

/* Function: symtable_print_labels
* --------------------------------
* Prints the current symbol table to the console.
*/
void symtable_print_labels()
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        if (hashArray[i] != NULL)
        {
            printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
        }
    }
}
