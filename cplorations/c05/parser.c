/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Alex Miesbauer
 * [TERM] FALL 2023
 *
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s)
{
    int len = strlen(s) + 1;
    char s_new[len];
    int i = 0;

    for(char* s2 = s; *s2; s2++)
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
 * -------------
 * iterate each line in the file and strip whitespace and comments.
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE *file)
{
    char line[MAX_LINE_LENGTH] = {0};
    while (fgets(line, sizeof(line), file))
    {
        strip(line);
        if (!*line)
        {
            continue;
        }

        char inst_type;
        if (is_Atype(line))
        {
            inst_type = 'A';
        }
        
        if (is_label(line))
        {
            inst_type = 'L';
        }

        if (is_Ctype(line))
        {
            inst_type = 'C';
        }

        printf("%c  %s\n", inst_type, line);
    }
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