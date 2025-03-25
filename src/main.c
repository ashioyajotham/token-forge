#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file '%s'\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        exit(1);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Read input file
    char *source = read_file(argv[1]);
    
    // Initialize lexer
    Lexer *lexer = init_lexer(source);
    
    // Test lexer by printing all tokens
    Token *token;
    while ((token = lexer_get_next_token(lexer))->type != TOKEN_EOF) {
        printf("Token(type=%d, value='%s', line=%d, column=%d)\n",
               token->type,
               token->value ? token->value : "EOF",
               token->line,
               token->column);
        free(token->value);
        free(token);
    }
    
    // Clean up
    free(token);
    lexer_free(lexer);
    free(source);
    
    return 0;
}
