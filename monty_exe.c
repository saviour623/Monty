#include "monty.h"
extern _global_tmp glbstack_s;
//stk_line
//stk_stque
void monty_push_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *new_stack = malloc(sizeof(stack_t));

	if (new_stack == NULL)
	{
		fprintf(stderr, "ERROR: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	if (!(glbstack_s.stk_mode & S_VALNPUT))
	{
		fprintf(stderr, "L<%u>: usage: push integer\n", glbstack_s.stk_line);
		exit(EXIT_FAILURE);
	}
	if (*stack == NULL)
	{
		new_stack->prev = new_stack->next = NULL;
		new_stack->n = line_number;
		*stack = new_stack;
		/* update the global stack head */
		glbstack_s.stk_stque = stack;
	}
	else
	{
		new_stack->n = line_number;
		new_stack->prev = *stack;
		new_stack->next = NULL;
		(*stack)->next = new_stack;
		*stack = new_stack;
	}
	glbstack_s.stk_counter += 1;
}
void monty_pop_stack(stack_t **stack, unsigned int line_number __unused__)
{
	stack_t *ptr;
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L<%u>: can't pop an empty stack\n", glbstack_s.stk_line);
		exit(EXIT_FAILURE);
	}
	ptr = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(ptr);
	ptr = NULL;

	glbstack_s.stk_counter -= 1;
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
	{
		fprintf(stderr, "L<%u>: can't pint, stack empty\n", glbstack_s.stk_line);
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "%u\n", (*stack)->n);
}
void monty_swap_stack(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L<%u>: can't swap, stack empty\n", glbstack_s.stk_line);
		exit(EXIT_FAILURE);
	}
	else if (glbstack_s.stk_counter < 2)
	{
		fprintf(stderr, "L<%u>: can't swap, stack too short\n", glbstack_s.stk_line);
		exit(EXIT_FAILURE);
	}
	(*stack)->n ^= (*stack)->prev->n;
	(*stack)->prev->n ^= (*stack)->n;
	(*stack)->n ^= (*stack)->prev->n;
}
void monty_add_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *ptr;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L<%u>: can't swap, stack empty\n", glbstack_s.stk_line);
		exit(EXIT_FAILURE);
	}
	else if (glbstack_s.stk_counter < 2)
	{
		fprintf(stderr, "L<%u>: can't add, stack too short\n", glbstack_s.stk_line);
		exit(EXIT_FAILURE);
	}
	ptr = *stack;
	(*stack)->prev->n += (*stack)->n;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(ptr);
	ptr = NULL;

	glbstack_s.stk_counter -= 1;

}
void monty_sub_stack(stack_t **stack, unsigned int line_number)
{
}
void monty_nop_stack(stack_t **stack __unused__, unsigned int line_number __unused__)
{
	/* do nothing */
}
