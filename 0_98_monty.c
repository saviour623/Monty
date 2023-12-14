#include "monty.h"
#include <stdbool.h>

/**
 * delimCharcmp - check if a char is a delimiter.
 * @delim: delimiter
 * @cmp: character
 * Return: true if it a delimiter, else false
 */
int delimCharcmp(const char *restrict delim, const char *restrict cmp)
{
	char c __unused__;

	if (delim == NULL || cmp == NULL)
		return (-1);

	if (delim[0] != 0 && delim[1] == 0)
		return *delim == *cmp;

	for (; (c = *delim); delim++)
	{
		if (c == *cmp)
			return (true);
	}
	return (false);
}
int getNumtoks(const char *__restrict__ st, const char *__restrict__ delim)
{
	bool set;
	register int oo;

	if (st == NULL || delim == NULL)
		return -1;

	if (*st == '\0' || *delim == '\0')
		return 0;

	oo = 0;
	set = true;

	for (; *st; (void)*st++)
	{
		if (delimCharcmp(delim, st))
			set = true;
		else if (set)
		{
			oo++;
			set = false;
		}
	}
	return oo;
}
char **getcmdstring(char *__restrict__ arg)
{
	char *delim = " \t\r\n";
	char **buftok;
	char *token = NULL;
	int oo;

	if ((arg == NULL) || (*arg == '\0'))
		return NULL;

	buftok = malloc((sizeof(char *) * (getNumtoks(arg, delim))) + 1);

	if (buftok == NULL)
	{
		fprintf(stderr, "ERROR: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	token = arg;
	for (oo = 0; (token = strtok(token, delim)) != NULL; oo++)
	{
		buftok[oo] = token;
		token = NULL;
	}

	buftok[oo] = NULL;
	return buftok;
}

#define _MAP_OP_INSTRUCTION_R()\
	{														\
		{"push", monty_push_stack}, {"pop", monty_pop_stack}			\
		,{"pall", monty_print_stack}, {"pint", monty_pint_stack}		\
		,{"swap", monty_swap_stack}, {"add", monty_add_stack}			\
		,{"sub", monty_sub_stack}, {"nop", monty_nop_stack}, NULL			\
	}
int main(int argc, char **argv)
{
	register int oo, lncnt = 1;
	FILE *F;
	char *bytefile = NULL;
	char *ln = NULL, *tmp, **instrc = NULL;
	size_t rd = 0;
	instruction_t op_routine[] = _MAP_OP_INSTRUCTION_R();
	stack_t *monty_stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "%s\n", "USAGE: monty file");
		exit(EXIT_FAILURE);
	}
	bytefile = argv[argc - 1];
	F = fopen(bytefile, "r");

	if (F == NULL)
	{
		fprintf(stderr, "Error: Can't open file <%s>\n", bytefile);
		exit(EXIT_FAILURE);
	}
	while (lncnt++)
	{
		if (getline(&ln, &rd, F) == -1)
		{
			if (errno == ENOMEM)
			{
				fprintf(stderr, "Error: Can't open file <%s>\n", bytefile);
				exit(EXIT_FAILURE);
			}
			break;
		}
		/* get the instructions from each line */
		instrc = getcmdstring(ln);
		for (oo = 0; (tmp = op_routine[oo].opcode) != NULL; oo++)
		{
			if (strcmp(tmp, *instrc) == 0)
				op_routine[oo].routine(&monty_stack, lncnt);
		}
		/* if tmp ever gets to null, that means there isn't any opcode that matches the inputed instruction */
		if (tmp == NULL)
		{
			fprintf(stderr, "L<%d>: unknown instruction <%s>\n", lncnt, ln);
			/* TODO: do cleanup here */
			exit(EXIT_FAILURE);
		}
		rd = 0;
		free(ln);
		ln = NULL;
	}
/* TODO: do clean up here */
	if (fclose(F) == EOF)
	{
		perror("flcose");
		exit(EXIT_FAILURE);
	}
	return 0;
}
