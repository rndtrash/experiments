/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"

#define GOTO_IF_SUCCESS(x) {if(x) goto parse;}

// global
char c = 0;
token_array *tokenArray;

bool p_text()
{
	token *t = malloc(sizeof(token));
	*t = (token) {TEXT, NULL, 0};
	t->value = malloc(MAX_STRING_SIZE * sizeof(char));
	size_t currentPosition = 0;
	do
	{
		if (!isalpha(c))
		{
			if (currentPosition == 0)
			{
				DEBUG("Token is not a text")
				free(t->value);
				free(t);
				return false;
			}
			else
				break;
		}

		t->value[currentPosition++] = c;
		if (currentPosition == MAX_STRING_SIZE * sizeof(char) - 1)
			break;
	}
	while ((c = getchar()) != EOF);
	t->value[currentPosition] = '\0';
	t->size = currentPosition;
	ta_append(tokenArray, t);
	return true;
}

bool p_space()
{
	token *t = malloc(sizeof(token));
	*t = (token) {SPACE, NULL, 0};
	t->value = malloc(MAX_STRING_SIZE * sizeof(char));
	size_t currentPosition = 0;
	do
	{
		if (!isblank(c))
		{
			if (currentPosition == 0)
			{
				DEBUG("Token is not a blank character")
				free(t->value);
				free(t);
				return false;
			}
			else
				break;
		}

		t->value[currentPosition++] = c;
		if (currentPosition == MAX_STRING_SIZE * sizeof(char) - 1)
			break;
	}
	while ((c = getchar()) != EOF);
	t->value[currentPosition] = '\0';
	t->size = currentPosition;
	ta_append(tokenArray, t);
	return true;
}

bool p_nl()
{
	token *t = malloc(sizeof(token));
	*t = (token) {NEW_LINE, NULL, 0};
	t->value = malloc(MAX_STRING_SIZE * sizeof(char));
	size_t currentPosition = 0;
	do
	{
		if (c != '\r' && c != '\n')
		{
			if (currentPosition == 0)
			{
				DEBUG("Token is not a new line character")
				free(t->value);
				free(t);
				return false;
			}
			else
				break;
		}

		t->value[currentPosition++] = c;
		if (currentPosition == MAX_STRING_SIZE * sizeof(char) - 1)
			break;
	}
	while ((c = getchar()) != EOF);
	t->value[currentPosition] = '\0';
	t->size = currentPosition;
	ta_append(tokenArray, t);
	return true;
}

int main()
{
	tokenArray = ta_new(1);

	while((c = getchar()) != EOF)
	{
		parse:
		printf("Got %" PR_SIZET "u tokens\n", tokenArray->length);
		GOTO_IF_SUCCESS(p_text())
		GOTO_IF_SUCCESS(p_space())
		GOTO_IF_SUCCESS(p_nl())
		if (c == EOF)
			break;
		printf("%s%c%s\n", "Warning: unknown token! Last character was: \"", c,"\"");
	}

	ta_free(tokenArray);
	return 0;
}
