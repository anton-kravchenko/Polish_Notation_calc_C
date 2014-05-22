#include <stddef.h>
#ifndef TOKEN_H_
#define TOKEN_H_

typedef struct
{
	union {double value; char c;} data;
	enum {UNDEF, NUMBER, OPERATOR, OPEN_BRACE, CLOSE_BRACE} type;
} Token;

#endif
