#include "monty.h"
#include <stdbool.h>
_global_tmp glbstack_s;

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

#define _MAP_OP_INSTRUCTION_R()											\
	{																	\
		{"push", monty_push_stack}, {"pop", monty_pop_stack}			\
			,{"pall", monty_print_stack}, {"pint", monty_pint_stack}	\
			,{"swap", monty_swap_stack}, {"add", monty_add_stack}		\
			,{"sub", monty_sub_stack}, {"nop", monty_nop_stack}			\
			,{"div", monty_div_stack}, {"mul", monty_mul_stack}			\
			,{"mod", monty_mod_stack}, {"pchar", monty_pchar_stack}		\
			,{"pstr", monty_pstr_stack}, {"rot", monty_rot_stack}		\
			,{"rotl", monty_rotl_stack}, {"rotr", monty_rotr_stack}		\
			,{"stack", monty_stack}, {"queue", monty_queue}				\
			,{NULL, NULL}												\
	}
/* get integer */
#include <limits.h>
int get_int(char *s, int *vlue)
{
	register long int n = 0, sgn = 1;
	register int c;
	if (s == NULL || vlue == NULL || *s == 0)
		return -1;
	if (*s == '-')
	{
		sgn = -1;
		s++;
	}
	for (; (c = *s); s++)
	{
		if ((c < 48 || c > 57) || n > INT_MAX)
			return ((n = 0), -1);
		n = ((n << 3) + (n << 1)) + (c - 48);
	}
	*vlue = sgn * n;
	return 0;
}
int main(int argc, char **argv)
{
	register int oo, lncnt = 1;
	FILE *F;
	char *bytefile = NULL;
	char *ln = NULL, *tmp, **instrc = NULL;
	size_t rd = 0;
	int vlue;
	instruction_t op_routine[] = _MAP_OP_INSTRUCTION_R();
	stack_t *monty_stack = NULL, *stack_pointer = NULL;
	struct stat statbf;

	if (argc != 2)
	{
		fprintf(stderr, "%s\n", "USAGE: monty file");
		exit(EXIT_FAILURE);
	}
	bytefile = argv[argc - 1];
	if (stat(bytefile, &statbf) == -1 || (statbf.st_mode & S_IFMT) != S_IFREG)
		goto openErr;
	F = fopen(bytefile, "r");
	if (F == NULL)
	{
	openErr:
		fprintf(stderr, "Error: Can't open file <%s>\n", bytefile);
		exit(EXIT_FAILURE);
	}
	glbstack_s.stk_mode |= S_OPSTACK;
	for (; true; lncnt++)
	{
		if (getline(&ln, &rd, F) == -1)
		{
			if (errno == ENOMEM)
			{
				fprintf(stderr, "Error: malloc failed\n");
				exit(EXIT_FAILURE);
			}
			break;
		}
		/* get the instructions from each line */
		instrc = getcmdstring(ln);
		for (oo = 0; (tmp = op_routine[oo].opcode) != NULL; oo++)
		{
			/* comment */
			if (**instrc == '#')
				goto reuse;
			if (strcmp(tmp, *instrc) == 0)
			{
				/* TODO: if opcode requires a value and none is given or an errorneous value is given raise an error */
				glbstack_s.stk_line = lncnt;
				glbstack_s.stk_mode |= !(get_int(instrc[1], &vlue)) & S_VALNPUT;
				op_routine[oo].routine(&monty_stack, vlue);
				goto reuse;
			}
		}
		/* if tmp ever gets to null, that means there isn't any opcode that matches the inputed instruction */
		if (tmp == NULL)
		{
			fprintf(stderr, "L<%d>: unknown instruction <%s>\n", lncnt, ln);
			/* TODO: do cleanup here */
			exit(EXIT_FAILURE);
		}
	reuse:
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
