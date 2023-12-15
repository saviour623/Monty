#include "monty.h"
void monty_push_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *new_stack = malloc(sizeof(stack_t));

	if (new_stack == NULL)
	{
		fprintf(stderr, "ERROR: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	if (*stack == NULL)
	{
		new_stack->prev = new_stack->next = NULL;
		new_stack->n = line_number;
		*stack = new_stack;
	}
	else
	{
		new_stack->n = line_number;
		new_stack->prev = *stack;
		new_stack->next = NULL;
		(*stack)->next = new_stack;
		*stack = new_stack;
	}
}
void monty_pop_stack(stack_t **stack, unsigned int line_number __unused__)
{
}
void monty_print_stack(stack_t **stack, unsigned int line_number)
{
	register stack_t *iter = *stack;

	if (iter == NULL || stack == NULL)
		return;
	while (iter != NULL)
	{
		fprintf(stdout, "%u\n", iter->n);
		iter = iter->prev;
	}
}
void monty_pint_stack(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
		fprintf(stderr, "L<line_number>: can't pint, stack empty");
	fprintf(stdout, "%u\n", (*stack)->n);
}
void monty_swap_stack(stack_t **stack, unsigned int line_number)
{
}
void monty_add_stack(stack_t **stack, unsigned int line_number)
{
}
void monty_sub_stack(stack_t **stack, unsigned int line_number)
{
}
void monty_nop_stack(stack_t **stack, unsigned int line_number)
{
}
