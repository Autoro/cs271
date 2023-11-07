/****************************************
 * C-ploration 7 for CS 271
 *
 * [NAME] Alex Miesbauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

typedef struct Symbol
{
    char* name;
    hack_addr addr;
} Symbol;

int hash(char* str);
Symbol* symtable_find(char* key);
void symtable_insert(char* key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();
