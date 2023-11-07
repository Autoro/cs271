/****************************************
 * C-ploration 7 for CS 271
 *
 * [NAME] Alex Miesbauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type
{
    Invalid = -1,
    A,
    C
};

typedef struct c_instruction
{
    opcode a : 1;
    opcode comp : 6;
    opcode dest : 3;
    opcode jump : 3;
} c_instruction;

typedef struct a_instruction
{
    union a_instruction_union
    {
        hack_addr address;
        char* label;
    } value;
    bool is_addr;
} a_instruction;

typedef struct instruction
{
    union instruction_union
    {
        a_instruction a_instr;
        c_instruction c_instr;
    } value;
} instruction;

/** function prototypes **/
char* strip(char* s);

void parse(FILE* file);

void print_line(char inst_type, const char* line);

bool is_Atype(const char* line);

bool is_label(const char* line);

bool is_Ctype(const char* line);

char* extract_label(const char* line, char* label);