#ifndef PARSER_H
#define PARSER_H

#include <assert.h>
#include <stdint.h>

#include "tools.h"

#define MAX_STRING_SIZE 32

typedef enum
{
	TEXT = 0,
	NUMBER,
	HEXADECIMAL_SEPARATOR,
	BINARY_SEPARATOR,
	SPACE,
	COMMA,
	COMMENT,
	NEW_LINE
} TOKEN_TYPE;

typedef struct
{
	TOKEN_TYPE tokenType;
	char *value;
	size_t size;
} token;

typedef struct
{
	token **tokens;
	size_t length;
	size_t size;
	size_t allocated;
} token_array;

token_array *ta_new(size_t initialSize);
void ta_free(token_array *tokenArray);
void ta_append(token_array *tokenArray, token *t);

token_array *ta_new(size_t initialSize)
{
	token_array* tokenArray = malloc(sizeof(token_array));
	assert(tokenArray != NULL);
	tokenArray->length = 0;
	tokenArray->size = 0;
	tokenArray->allocated = initialSize * sizeof(token);
	tokenArray->tokens = malloc(tokenArray->allocated);
	assert(tokenArray->tokens != NULL);

	return tokenArray;
}

void ta_free(token_array *tokenArray)
{
	printf("%s %" PR_SIZET "u %s", "Removing", tokenArray->length, "tokens...\n");
	for (size_t i = 0; i < tokenArray->length; i++)
	{
		printf("%i %s %" PR_SIZET "u\n",
			tokenArray->tokens[i]->tokenType,
			tokenArray->tokens[i]->value,
			tokenArray->tokens[i]->size);
		free(tokenArray->tokens[i]->value);
		free(tokenArray->tokens[i]);
	}
	free(tokenArray->tokens);
	free(tokenArray);
}

void ta_append(token_array *tokenArray, token *t)
{
	tokenArray->length++;
	tokenArray->size = tokenArray->length * sizeof(token);
	if (tokenArray->size > tokenArray->allocated)
	{
		token **tokens = realloc(tokenArray->tokens, tokenArray->size);
		assert(tokens != NULL);
		tokenArray->tokens = tokens;
		tokenArray->allocated = tokenArray->size;
	}

	tokenArray->tokens[tokenArray->length - 1] = t;
}

#endif
