
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

// List of C keywords
const char *keywords[] =
{
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while", "inline", "restrict",
    "_Bool", "_Complex", "_Imaginary"
};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

// Check whether a word is a C keyword
int is_keyword(const char *word)
{
    int i;

    for (i = 0; i < KEYWORD_COUNT; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

// Convert token type into a printable string
const char *get_token_name(TokenType type)
{
    switch (type)
    {
        case KEYWORD:
            return "KEYWORD";

        case IDENTIFIER:
            return "IDENTIFIER";

        case CONSTANT:
            return "CONSTANT";

        case STRING_LITERAL:
            return "STRING_LITERAL";

        case CHARACTER_LITERAL:
            return "CHARACTER_LITERAL";

        case OPERATOR:
            return "OPERATOR";

        case SPECIAL_SYMBOL:
            return "SPECIAL_SYMBOL";

        default:
            return "UNKNOWN";
    }
}

// Display a token
void print_token(TokenType type, const char *lexeme, int line)
{
    printf("%-18s %-25s %d\n",
           get_token_name(type), lexeme, line);
}

// Operators are checked longest-first.
// This prevents "==" from being read as two "=" operators.
const char *operators[] =
{
    ">>=", "<<=", "...",
    "++", "--", "->",
    "+=", "-=", "*=", "/=", "%=",
    "==", "!=", "<=", ">=",
    "&&", "||",
    "<<", ">>",
    "&=", "|=", "^=",
    "+", "-", "*", "/", "%",
    "=", "<", ">", "!",
    "&", "|", "^", "~",
    "?", ":", "."
};

#define OPERATOR_COUNT \
    (sizeof(operators) / sizeof(operators[0]))

// Check whether a character is a special symbol
int is_special_symbol(char ch)
{
    return strchr("(){}[];,", ch) != NULL;
}

// Analyze the source code
void analyze_source(const char *source)
{
    int i = 0;
    int line = 1;

    char lexeme[MAX_TOKEN_LENGTH];

    printf("\n%-18s %-25s %s\n",
           "TOKEN TYPE", "LEXEME", "LINE");

    printf("----------------------------------------------------\n");

    while (source[i] != '\0')
    {
        int j = 0;
        int matched = 0;

        // Ignore whitespace
        if (isspace((unsigned char)source[i]))
        {
            if (source[i] == '\n')
            {
                line++;
            }

            i++;
            continue;
        }

        // Ignore single-line comments: // comment
        if (source[i] == '/' && source[i + 1] == '/')
        {
            while (source[i] != '\0' && source[i] != '\n')
            {
                i++;
            }

            continue;
        }

        // Ignore multi-line comments: /* comment */
        if (source[i] == '/' && source[i + 1] == '*')
        {
            i += 2;

            while (source[i] != '\0')
            {
                if (source[i] == '\n')
                {
                    line++;
                }

                if (source[i] == '*' && source[i + 1] == '/')
                {
                    i += 2;
                    break;
                }

                i++;
            }

            continue;
        }

        // Identify identifiers and keywords
        if (isalpha((unsigned char)source[i]) ||
            source[i] == '_')
        {
            while (isalnum((unsigned char)source[i]) ||
                   source[i] == '_')
            {
                if (j < MAX_TOKEN_LENGTH - 1)
                {
                    lexeme[j++] = source[i];
                }

                i++;
            }

            lexeme[j] = '\0';

            if (is_keyword(lexeme))
            {
                print_token(KEYWORD, lexeme, line);
            }
            else
            {
                print_token(IDENTIFIER, lexeme, line);
            }

            continue;
        }

        // Identify numeric constants
        if (isdigit((unsigned char)source[i]))
        {
            int has_dot = 0;

            while (isdigit((unsigned char)source[i]) ||
                   (source[i] == '.' &&
                    !has_dot &&
                    isdigit((unsigned char)source[i + 1])))
            {
                if (source[i] == '.')
                {
                    has_dot = 1;
                }

                if (j < MAX_TOKEN_LENGTH - 1)
                {
                    lexeme[j++] = source[i];
                }

                i++;
            }

            lexeme[j] = '\0';

            print_token(CONSTANT, lexeme, line);
            continue;
        }

        // Identify string literals
        if (source[i] == '"')
        {
            int closed = 0;

            lexeme[j++] = source[i++];

            while (source[i] != '\0')
            {
                char ch = source[i++];

                if (j < MAX_TOKEN_LENGTH - 1)
                {
                    lexeme[j++] = ch;
                }

                if (ch == '\\' && source[i] != '\0')
                {
                    ch = source[i++];

                    if (j < MAX_TOKEN_LENGTH - 1)
                    {
                        lexeme[j++] = ch;
                    }

                    if (ch == '\n')
                    {
                        line++;
                    }

                    continue;
                }

                if (ch == '"')
                {
                    closed = 1;
                    break;
                }

                if (ch == '\n')
                {
                    line++;
                }
            }

            lexeme[j] = '\0';

            if (closed)
            {
                print_token(STRING_LITERAL, lexeme, line);
            }
            else
            {
                print_token(UNKNOWN, lexeme, line);
            }

            continue;
        }

        // Identify character literals
        if (source[i] == '\'')
        {
            int closed = 0;

            lexeme[j++] = source[i++];

            while (source[i] != '\0')
            {
                char ch = source[i++];

                if (j < MAX_TOKEN_LENGTH - 1)
                {
                    lexeme[j++] = ch;
                }

                if (ch == '\\' && source[i] != '\0')
                {
                    ch = source[i++];

                    if (j < MAX_TOKEN_LENGTH - 1)
                    {
                        lexeme[j++] = ch;
                    }

                    continue;
                }

                if (ch == '\'')
                {
                    closed = 1;
                    break;
                }

                if (ch == '\n')
                {
                    line++;
                    break;
                }
            }

            lexeme[j] = '\0';

            if (closed)
            {
                print_token(CHARACTER_LITERAL, lexeme, line);
            }
            else
            {
                print_token(UNKNOWN, lexeme, line);
            }

            continue;
        }

        // Identify operators by checking the longest matches first
        for (j = 0; j < OPERATOR_COUNT; j++)
        {
            size_t length = strlen(operators[j]);

            if (strncmp(&source[i], operators[j], length) == 0)
            {
                print_token(OPERATOR, operators[j], line);

                i += (int)length;
                matched = 1;
                break;
            }
        }

        if (matched)
        {
            continue;
        }

        // Identify special symbols
        if (is_special_symbol(source[i]))
        {
            lexeme[0] = source[i];
            lexeme[1] = '\0';

            print_token(SPECIAL_SYMBOL, lexeme, line);

            i++;
            continue;
        }

        // Report any unsupported or unrecognized character
        lexeme[0] = source[i];
        lexeme[1] = '\0';

        print_token(UNKNOWN, lexeme, line);

        i++;
    }
}
