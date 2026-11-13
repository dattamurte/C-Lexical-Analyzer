
#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 256

// Different types of tokens
typedef enum
{
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    STRING_LITERAL,
    CHARACTER_LITERAL,
    OPERATOR,
    SPECIAL_SYMBOL,
    UNKNOWN
} TokenType;

// Structure to store information about a token
typedef struct
{
    TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
    int line_number;
} Token;

// Function declaration
void analyze_source(const char *source);

#endif
