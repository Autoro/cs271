/****************************************
* C-ploration 10 for CS 271
*
* [NAME] Alex Miesbauer
* [TERM] FALL 2023
*
****************************************/
#include "error.h"
#include "parser.h"
#include "symtable.h"

/* Function: strip
* ----------------
* remove whitespace and comments from a line
*
* s: the char* string to strip
*
* returns: the stripped char* string
*/
char* strip(char* s)
{
    int len = strlen(s) + 1;
    char s_new[len];
    int i = 0;

    for (char* s2 = s; *s2; s2++)
    {
        if (*s2 == '/' && *(s2 + 1) == '/')
        {
            break;
        }
        else if (!isspace(*s2))
        {
            s_new[i++] = *s2;
        }
    }

    s_new[i] = '\0';
    strcpy(s, s_new);

    return s;
}

/* Function: parse
* ----------------
* iterate each line in the file and strip whitespace and comments.
*
* file: pointer to FILE to parse
*
* returns: nothing
*/
int parse(FILE* file, instruction* instructions)
{
    char line[MAX_LINE_LENGTH] = { 0 };
    int instr_num = 0;
    int line_num = 0;
    instruction instr;

    add_predefined_symbols();

    while (fgets(line, sizeof(line), file))
    {
        line_num++;

        if (instr_num > MAX_INSTRUCTIONS)
        {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }

        strip(line);
        if (!*line)
        {
            continue;
        }

        if (is_Atype(line))
        {
            if (!parse_A_instruction(line, &instr.instr.a))
            {
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }

            instr.itype = INSTR_A;

            if (instr.instr.a.is_addr)
            {
                printf("A: %d\n", instr.instr.a.operand.address);
            }
            else
            {
                printf("A: %s\n", instr.instr.a.operand.label);
            }
        }
        else if (is_label(line))
        {
            char label[MAX_LABEL_LENGTH] = { 0 };
            extract_label(line, label);

            if (!isalpha(label[0]))
            {
                exit_program(EXIT_INVALID_LABEL, line_num, label);
            }

            if (symtable_find(label) != NULL)
            {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
            }

            symtable_insert(label, instr_num);

            continue;
        }
        else if (is_Ctype(line))
        {
            char temp_line[MAX_LINE_LENGTH];
            strcpy(temp_line, line);

            parse_C_instruction(temp_line, &instr.instr.c);

            if (instr.instr.c.dest == DEST_INVALID)
            {
                exit_program(EXIT_INVALID_C_DEST);
            }

            if (instr.instr.c.comp == COMP_INVALID)
            {
                exit_program(EXIT_INVALID_C_COMP);
            }

            if (instr.instr.c.jump == JMP_INVALID)
            {
                exit_program(EXIT_INVALID_C_JUMP);
            }

            instr.itype = INSTR_C;

            printf("C: d=%d, c=%d, j=%d\n", instr.instr.c.dest, instr.instr.c.comp, instr.instr.c.jump);
        }

        instructions[instr_num++] = instr;
    }

    return instr_num;
}

/* Function: is_Atype
* -------------------
* Determines if the line contains an A instruction.
*
* line: A pointer to the line to check.
*
* returns: True if the line is an A instruction, otherwise false.
*/
bool is_Atype(const char* line)
{
    return line[0] == '@';
}

/* Function: is_line
* -------------------
* Determines if the line contains a label.
*
* line: A pointer to the line to check.
*
* returns: True if the line is an label, otherwise false.
*/
bool is_label(const char* line)
{
    int length = strlen(line);

    return line[0] == '(' && line[length - 1] == ')';
}

/* Function: is_Ctype
* -------------------
* Determines if the line contains an C instruction.
*
* line: A pointer to the line to check.
*
* returns: True if the line is an C instruction, otherwise false.
*/
bool is_Ctype(const char* line)
{
    return !(is_Atype(line) || is_label(line));
}

/* Functcion: extract_label
* -------------------------
* Extracts the name of the label from a line containing a Hack label.
*
* line: A pointer to the line to extract the label from.
* label: Contains the label extract from the line when the function ends.
*
* returns: A pointer to the label that was extracted.
*/
char* extract_label(const char* line, char* label)
{
    int i = 0;
    // line + 1 skips the first opening parenthesis.
    for (const char* lineptr = line + 1; *lineptr != ')'; lineptr++)
    {
        label[i++] = *lineptr;
    }

    label[i] = '\0';

    return label;
}

/* Function: add_predefined_symbols
* ---------------------------------
* Adds the predefined symbols from the Hack language to the symbol table.
*/
void add_predefined_symbols()
{
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++)
    {
        predefined_symbol symbol = predefined_symbols[i];
        symtable_insert(symbol.name, symbol.address);
    }
}

/* Function: parse_A_instruction
* ------------------------------
* Parses an A instruction from a given line.
*
* line: The line to parse the A instrution from.
* instr: The a_instruction that will store the parsed information.
*
* returns: True if the instruction was successfully parsed, otherwise false.
*/
bool parse_A_instruction(const char* line, a_instruction* instr)
{
    // Duplicate line starting at one character passed the @ symbol.
    char* s = strdup(line + 1);
    char* str_end = NULL;
    long result = strtol(s, &str_end, 10);

    // A instruction is a label reference.
    if (s == str_end)
    {
        instr->operand.label = strdup(line);
        instr->is_addr = false;
    }
    // A instruction is invalid.
    else if (*str_end != 0)
    {
        return false;
    }
    // A instruction is an address.
    else
    {
        instr->operand.address = result;
        instr->is_addr = true;
    }

    return true;
}

/* Function parse_C_instruction
* -----------------------------
* Parses a C instruction from the given line.
*
* line: The line to parse the C instruction from.
* instr: The c_instruction that will store the parsed information.
*/
void parse_C_instruction(char * line, c_instruction * instr)
{
    char* temp = strtok(line, ";");
    char* jump = strtok(NULL, ";");
    char* dest = strtok(temp, "=");
    char* comp = strtok(NULL, "=");

    // If comp is NULL then the optional dest was missing in the instruction.
    if (comp == NULL)
    {
        comp = dest;
        dest = NULL;
    }

    int a = 0;
    instr->comp = str_to_compid(comp, &a);
    instr->a = a;

    instr->dest = str_to_destid(dest);
    instr->jump = str_to_jumpid(jump);
}
