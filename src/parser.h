#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// AST Node Types
typedef enum {
    NODE_BINARY_OP,
    NODE_NUMBER,
    NODE_IDENTIFIER
} NodeType;

// AST Node Structure
typedef struct ASTNode {
    NodeType type;
    Token *token;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

// Parser Structure
typedef struct {
    Lexer *lexer;
    Token *current_token;
} Parser;

// Parser functions
Parser* init_parser(Lexer *lexer);
ASTNode* parser_parse(Parser *parser);
void parser_free(Parser *parser);
void ast_free(ASTNode *node);

#endif // PARSER_H
