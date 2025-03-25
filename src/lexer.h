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

// Error handling
typedef enum {
    ERROR_NONE,
    ERROR_INVALID_CHAR,
    ERROR_INVALID_IDENTIFIER,
    ERROR_IDENTIFIER_STARTS_WITH_NUMBER,
    ERROR_IDENTIFIER_TOO_LONG
} LexerError;

// Token structure
typedef struct {
    TokenType type;
    char *value;
    int line;
    int column;
    LexerError error;
} Token;

// Lexer structure
typedef struct {
    char *input;
    int position;
    int line;
    int column;
    char current_char;
    LexerError last_error;
} Lexer;

// Lexer functions
Lexer* init_lexer(char *input);
void lexer_advance(Lexer *lexer);
void lexer_skip_whitespace(Lexer *lexer);
Token* lexer_get_next_token(Lexer *lexer);
void lexer_free(Lexer *lexer);

#endif // LEXER_H
