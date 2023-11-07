/****************************************
* C-ploration 7 for CS 271
*
* [NAME] Alex Miesbauer
* [TERM] FALL 2023
*
****************************************/
#include "parser.h"
#include "symtable.h"

int main(int argc, const char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE* fin = fopen(argv[1], "r");
	if (fin == NULL)
	{
		perror("Unable to read file!");
		exit(EXIT_FAILURE);
	}

	parse(fin);
	symtable_print_labels();

	fclose(fin);
}
