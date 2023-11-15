/****************************************
 * C-ploration 9 for CS 271
 *
 * [NAME] Alex Miesbauer
 * [TERM] FALL 2023
 *
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

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
    } operand;
    bool is_addr;
} a_instruction;

typedef struct instruction
{
    union instruction_union
    {
        a_instruction a;
        c_instruction c;
    } instr;
} instruction;

/** function prototypes **/
char* strip(char* s);
void parse(FILE* file);
void add_predefined_symbols();
bool is_Atype(const char* line);
bool is_label(const char* line);
bool is_Ctype(const char* line);
char* extract_label(const char* line, char* label);
bool parse_A_instruction(const char* line, a_instruction* instr);

#endif
