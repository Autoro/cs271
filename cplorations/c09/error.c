#include "error.h"
/****************************************
* C-ploration 9 for CS 271
*
* [NAME] Alex Miesbauer
* [TERM] FALL 2023
*
****************************************/

const char* error_messages[] =
{
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
    [EXIT_INVALID_A_INSTR] = "Line %u: %s : Invalid A-instruction operand"
};

void exit_program(exitcode code, ...)
{
    va_list arguments;
    va_start(arguments, code);

    printf("ERROR: ");
    vprintf(error_messages[code], arguments);
    printf("\n");

    va_end(arguments);
    exit(code);
}
