
#ifndef OUTLINE_H_
#define OUTLINE_H_

#include "stack.h"
#include "token.h"

void init_outline();
void push_to_outline(Token*);
void push_to_outline_in(Token*, int);
Token pop_from_outline();
bool outline_is_empty();
bool outline_is_empty();
int outline_size();
void show_outline();
void revert_outline();
void move(int);
void calc();

Token *outline[size_of_stack];

int outline_current;

void init_outline()
{
	int i = 0;
	for(; i < size_of_stack; i++)
		outline[i] = (Token*)malloc(sizeof(Token));


}
void push_to_outline(Token *token)
{
	outline[outline_current]->data.value = token->data.value;
	outline[outline_current]->type = token->type;
	outline_current++;
}

void push_to_outline_in(Token* token, int position)
{
	outline[position]->data.value = token->data.value;
	outline[position]->type = token->type;
}

Token pop_from_outline()
{
	return *outline[--outline_current];
}

bool outline_is_empty()
{
	return 0 == outline_current;
}
int outline_size()
{
//	printf("size - %d\n",((int)outline[outline_current]-(int)outline[0])/16);
	return outline_current;
}
void show_outline()
{
	while(!outline_is_empty())
	{
		Token t = pop_from_outline();
		if (NUMBER == t.type)
		printf("%.f", t.data.value);
		if(OPERATOR == t.type)
		printf("%c", t.data.c);
	}
	printf("\n");
}
void revert_outline()
{
	int i = 0;
	Token temp;
	for(; i < outline_current/2; i++)
	{
		temp = *outline[i];
		*outline[i] = *outline[outline_current-1-i];
		*outline[outline_current-1-i] = temp;
	}

}
void move(int from)
{
	int i = from - 3;
	for(; i > -1; i-- )
		*outline[i+2] = *outline[i];
}
void calc()
{
	int current = 0;
	int left, right;
	double result;
	Token t = *outline[current];
	Token a, b;
	while(outline_size() > 1)
	{
		if(OPERATOR == t.type)
		{
			a = *outline[--current];
			b = *outline[--current];

			right = a.data.value;
			left = b.data.value;

			switch(t.data.c)
			{
				case '+':result = left+right;break;
				case '-':result = left-right;break;
				case '*':result = left*right;break;
				case '/':result = (double)left/right;break;
			}
			a.data.value = result;
			current+=2;
			push_to_outline_in(&a, current);
			move(current);
			outline_current-=2;
		}
			t = *outline[++current];
	}
	t = *outline[current-1];
	printf("%.f", t.data.value);
}
#endif /* OUTLINE_H_ */
