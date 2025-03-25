#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Lexer* init_lexer(char *input) {
    Lexer *lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->input = input;
    lexer->position = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current_char = input[0];
    return lexer;
}

void lexer_advance(Lexer *lexer) {
    if (lexer->current_char != '\0') {
        lexer->position++;
        lexer->column++;
        if (lexer->current_char == '\n') {
            lexer->line++;
            lexer->column = 1;
        }
        lexer->current_char = lexer->input[lexer->position];
    }
}

void lexer_skip_whitespace(Lexer *lexer) {
    while (lexer->current_char != '\0' && isspace(lexer->current_char)) {
        lexer_advance(lexer);
    }
}

Token* create_token(TokenType type, char *value, int line, int column) {
    Token *token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = value ? strdup(value) : NULL;
    token->line = line;
    token->column = column;
    return token;
}

Token* lexer_get_next_token(Lexer *lexer) {
    while (lexer->current_char != '\0') {
        if (isspace(lexer->current_char)) {
            lexer_skip_whitespace(lexer);
            continue;
        }

        if (isalpha(lexer->current_char)) {
            // Handle identifiers
            char identifier[256] = {0};
            int i = 0;
            int col = lexer->column;
            
            while (lexer->current_char != '\0' && (isalnum(lexer->current_char) || lexer->current_char == '_')) {
                identifier[i++] = lexer->current_char;
                lexer_advance(lexer);
            }
            return create_token(TOKEN_IDENTIFIER, identifier, lexer->line, col);
        }

        if (isdigit(lexer->current_char)) {
            // Handle numbers
            char number[256] = {0};
            int i = 0;
            int col = lexer->column;
            
            while (lexer->current_char != '\0' && isdigit(lexer->current_char)) {
                number[i++] = lexer->current_char;
                lexer_advance(lexer);
            }
            return create_token(TOKEN_NUMBER, number, lexer->line, col);
        }

        // Handle operators and other symbols
        int col = lexer->column;
        char current = lexer->current_char;
        lexer_advance(lexer);

        switch (current) {
            case '+': return create_token(TOKEN_PLUS, "+", lexer->line, col);
            case '-': return create_token(TOKEN_MINUS, "-", lexer->line, col);
            case '*': return create_token(TOKEN_MULTIPLY, "*", lexer->line, col);
            case '/': return create_token(TOKEN_DIVIDE, "/", lexer->line, col);
            case '(': return create_token(TOKEN_LPAREN, "(", lexer->line, col);
            case ')': return create_token(TOKEN_RPAREN, ")", lexer->line, col);
            case '=': return create_token(TOKEN_EQUALS, "=", lexer->line, col);
            case ';': return create_token(TOKEN_SEMICOLON, ";", lexer->line, col);
        }
    }

    return create_token(TOKEN_EOF, NULL, lexer->line, lexer->column);
}

void lexer_free(Lexer *lexer) {
    free(lexer);
}
