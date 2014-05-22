#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "stack.h"
#include "outline.h"

int get_priority(Token*);
void push_rest_from_stack_to_outline();

int main(void)
{
	char *expression = "3*(2+5)+6/(3+3)";
	printf("%s = ", expression);
	int priority, temp_priority;
	init_outline();
	init_stack();

	Token *token = (Token*)malloc(sizeof(Token));

	while(*expression != '\0')
	{

		switch(*expression)
		{
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			token->data.value = *expression - '0';
			token->type = NUMBER;
			push_to_outline(token);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			token->data.c = *expression;
			token->type = OPERATOR;
			priority = get_priority(token);

			if(stack_is_empty())
			{
				push_to_stack(token);
			}else{
				Token t = pop_from_stack();
				temp_priority = get_priority(&t);
				if(priority < temp_priority)
				{
					while (priority < temp_priority)
					{
						push_to_outline(&t);
						if(!stack_is_empty())
						{
							t = pop_from_stack();
							temp_priority = get_priority(&t);
							priority = 100500;
						}else {
							break;
						}
					}
					push_to_stack(token);
				} else {
					push_to_stack(&t);
					push_to_stack(token);
				}
			}
			break;
		case '(':
			token->data.c = *expression;
			token->type = OPEN_BRACE;
			push_to_stack(token);
			break;
		case ')':
			token->type = CLOSE_BRACE;
			Token t = pop_from_stack();
			while('(' != t.data.c)
			{
				push_to_outline(&t);
				t = pop_from_stack();
			}

			break;
		}
		expression++;
	}

	push_rest_from_stack_to_outline();
//	revert_outline();
	outline_size();
//	show_outline();
	calc();

	return 0;
}

int get_priority(Token *token)
{
	if (('+' == token->data.c) || ('-' == token->data.c))
		return 2;
	if (('*' == token->data.c) || ('/' == token->data.c) || ('^' == token->data.c))
		return 3;
	return 1;
}
void push_rest_from_stack_to_outline()
{
	Token t;
	while(!stack_is_empty())
	{
		t = pop_from_stack();
		push_to_outline(&t);
	}
}
