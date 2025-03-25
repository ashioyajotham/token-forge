#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

// Token types
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EQUALS,
    TOKEN_SEMICOLON
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char *value;
    int line;
    int column;
} Token;

// Lexer structure
typedef struct {
    char *input;
    int position;
    int line;
    int column;
    char current_char;
} Lexer;

// Lexer functions
Lexer* init_lexer(char *input);
void lexer_advance(Lexer *lexer);
void lexer_skip_whitespace(Lexer *lexer);
Token* lexer_get_next_token(Lexer *lexer);
void lexer_free(Lexer *lexer);

#endif // LEXER_H
