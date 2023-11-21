/****************************************
* C-ploration 10 for CS 271
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
    EXIT_SYMBOL_ALREADY_EXISTS,

    // Error code 6 represents that the parser found an invalid A instruction.
    EXIT_INVALID_A_INSTR,

    // Error code 7 represents that the parser found a C instruction with an invalid destination part.
    EXIT_INVALID_C_DEST,

    // Error code 8 represents that the parser found a C instruction with an invalid compare part.
    EXIT_INVALID_C_COMP,

    // Error code 9 represent that the parser found a C instruction with an invalid jump part.
    EXIT_INVALID_C_JUMP
} exitcode;

void exit_program(exitcode code, ...);

#endif
