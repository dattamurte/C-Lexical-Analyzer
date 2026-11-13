# C Lexical Analyzer

## Project Overview

This project implements a basic Lexical Analyzer using the C programming language.

A Lexical Analyzer is the first phase of a compiler. It reads source code character by character and groups the characters into meaningful units called **tokens**.

This program reads a C source file, identifies different token types, and displays the token type, lexeme, and line number.

## Features

The lexical analyzer identifies the following token categories:

- **Keywords:** `int`, `char`, `if`, `else`, `return`, etc.
- **Identifiers:** Variable names and function names.
- **Constants:** Integer and basic decimal numeric constants.
- **String Literals:** Text enclosed in double quotes.
- **Character Literals:** Characters enclosed in single quotes.
- **Operators:** Arithmetic, relational, logical, assignment, and other supported operators.
- **Special Symbols:** Parentheses, braces, brackets, semicolons, and commas.
- **Unknown:** Unrecognized characters or unsupported input.

Additional features:

- Ignores single-line comments (`//`).
- Ignores multi-line comments (`/* */`).
- Tracks line numbers.
- Reads source code from a file.
- Supports specifying the input filename through command-line arguments.

## Technologies Used

- Programming Language: C
- Compiler: GCC
- Standard: C11
- Development Environment: Linux / Ubuntu / WSL

## Project Structure

```text
Lexical-Analyzer/
│
├── main.c
├── lexer.c
├── lexer.h
├── input.c
├── README.md
├── .gitignore
└── Makefile
```

## Compilation

Compile the project using:

```bash
gcc main.c lexer.c -o lexer -Wall -Wextra -std=c11
```

Alternatively, use the Makefile:

```bash
make
```

## Execution

To analyze the default input file:

```bash
./lexer
```

To analyze another C source file:

```bash
./lexer filename.c
```

For example:

```bash
./lexer input.c
```

## Sample Output

```text
Lexical Analyzer
Source file: input.c

TOKEN TYPE         LEXEME                    LINE
----------------------------------------------------
KEYWORD            int                       5
IDENTIFIER         main                      5
SPECIAL_SYMBOL     (                         5
SPECIAL_SYMBOL     )                         5
SPECIAL_SYMBOL     {                         6
KEYWORD            int                       7
IDENTIFIER         a                         7
OPERATOR           =                         7
CONSTANT           20                        7
SPECIAL_SYMBOL     ;                         7
```

## Current Limitations

This is a basic lexical analyzer developed for learning and understanding lexical analysis.

- It does not implement the complete C language lexical grammar.
- Preprocessor directives are not fully recognized as separate tokens.
- Numeric constant recognition is limited to basic integer and decimal formats.
- Some advanced C literal formats and preprocessing features are not supported.

## Learning Outcomes

Through this project, I learned about:

- Lexical analysis and tokenization.
- C keywords and identifiers.
- String and character literals.
- Pointers and arrays.
- File handling using `fopen()`, `fread()`, and `fclose()`.
- Dynamic memory allocation using `malloc()` and `free()`.
- String handling using `<string.h>`.
- Character handling using `<ctype.h>`.
- Compilation and execution using GCC.

## Author

Developed as a C programming project to understand the fundamentals of lexical analysis.