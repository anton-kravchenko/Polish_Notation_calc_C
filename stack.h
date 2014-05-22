#include "token.h"

#ifndef STACK_
#define STACK_
#define size_of_stack 15

typedef char bool;
Token *empty = NULL;
Token *stack[size_of_stack];
int stack_current = 0;

void init_stack();
Token get_stack_top_cp();
void push_to_stack(Token*);
Token pop_from_stack();
bool stack_is_empty();

int size();
void show_stack();

void init_stack() {
	int i = 0;
	for (; i < size_of_stack; i++)
		stack[i] = (Token*) malloc(sizeof(Token));

}

Token get_stack_top_cp()
{
	return *stack[stack_current];
}
void push_to_stack(Token *token) {
	stack[stack_current]->data.c = token->data.c;
	stack[stack_current]->type = token->type;
//	printf("'%c', stack_current=%d\n", token->data.c, stack_current);
	stack_current++;
}

Token pop_from_stack() {
	return *stack[--stack_current];
}
bool stack_is_empty() {
	return 0 == stack_current;
}

int size() {
	return stack_current;
}
void show_stack() {
	while (0 == stack_is_empty()) {
		Token t = pop_from_stack();
		printf("%c ", t.data.c);
	}
}
#endif /* STACK_ */
