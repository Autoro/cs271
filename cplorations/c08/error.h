/****************************************
* C-ploration 8 for CS 271
*
* [NAME] Alex Miesbauer
* [TERM] FALL 2023
*
****************************************/
#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

typedef enum exitcode
{
    // Error code 1 represents that the program did not recieve the correct arguments.
    EXIT_INCORRECT_ARGUMENTS = 1,

    // Error code 2 represents that given file does not exist.
    EXIT_CANNOT_OPEN_FILE,

    // Error code 3 represents that too many instructions have been parsed.
    EXIT_TOO_MANY_INSTRUCTIONS,

    // Error code 4 represents that the parser found an invalid label.
    EXIT_INVALID_LABEL,

    // Error code 5 represents that the parser found a duplicate label.
    EXIT_SYMBOL_ALREADY_EXISTS
} exitcode;

void exit_program(exitcode code, ...);

#endif
