#ifndef _MONTY_H
#define _MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define _GNU_SOURCE
#if __GNUC__
#define __unused__ __attribute__((unused))
#else
#define __unused__ [[unused]]
#endif
#define S_OPQUEUE 0x04
#define S_OPSTACK 0x02
#define S_VALNPUT 0X01
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*routine)(stack_t **stack, unsigned int line_number);
} instruction_t;

typedef struct {
	stack_t *stk_stque;
	unsigned int stk_line;
	int stk_counter, stk_mode;
}  _global_tmp;

void monty_push_stack(stack_t **stack, unsigned int line_number);
void monty_pop_stack(stack_t **stack, unsigned int line_number);
void monty_print_stack(stack_t **stack, unsigned int line_number);
void monty_pint_stack(stack_t **stack, unsigned int line_number);
void monty_pchar_stack(stack_t **stack, unsigned int line_number);
void monty_pstr_stack(stack_t **stack, unsigned int line_number);
void monty_swap_stack(stack_t **stack, unsigned int line_number);
void monty_add_stack(stack_t **stack, unsigned int line_number);
void monty_sub_stack(stack_t **stack, unsigned int line_number);
void monty_div_stack(stack_t **stack, unsigned int line_number);
void monty_mod_stack(stack_t **stack, unsigned int line_number);
void monty_mul_stack(stack_t **stack, unsigned int line_number);
void monty_nop_stack(stack_t **stack, unsigned int line_number);
void monty_rot_stack(stack_t **stack, unsigned int line_number);
void monty_rotl_stack(stack_t **stack, unsigned int line_number);
void monty_rotr_stack(stack_t **stack, unsigned int line_number);
#endif
