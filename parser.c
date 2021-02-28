/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "parser.h"

// global
char c = 0;
token_array *tokenArray;

void trystring()
{
	token *t = malloc(sizeof(token));
	*t = (token) {STRING, NULL, MAX_STRING_SIZE * sizeof(char)};
	t->value = malloc(t->size);
	size_t currentPosition = 0;
	do
	{
		if (!isalpha(c))
			break;

		t->value[currentPosition++] = c;
		if (currentPosition == t->size - 1)
			break;
	}
	while ((c = getchar()) != EOF);
	t->value[currentPosition] = '\0';
	ta_append(tokenArray, t);
}

void trynl()
{
	// TODO:
}

int main()
{
	tokenArray = ta_new(1);

	while((c = getchar()) != EOF)
	{
		if (isalpha(c))
		{
			trystring();
		}
		//trynl();
		printf("%i\n", tokenArray->length);
	}

	ta_free(tokenArray);
	return 0;
}
