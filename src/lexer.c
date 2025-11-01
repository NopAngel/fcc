#include "fcc.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

static FILE *src_file = NULL;
static int current_line = 1;
static int current_char = ' ';

void fcc_init_lexer(const char *filename) {
    src_file = fopen(filename, "r");
    current_line = 1;
    current_char = ' ';
}

void fcc_close_lexer() {
    if (src_file) fclose(src_file);
}

static void next_char() {
    current_char = fgetc(src_file);
    if (current_char == '\n') current_line++;
}

Token fcc_next_token() {
    Token token = {T_UNKNOWN, "", current_line};
    
    if (!src_file || current_char == EOF) {
        token.type = T_EOF;
        return token;
    }
    

    while (isspace(current_char)) {
        next_char();
    }
    
    if (current_char == EOF) {
        token.type = T_EOF;
        return token;
    }
    

    if (isalpha(current_char) || current_char == '_') {
        int i = 0;
        while (isalnum(current_char) || current_char == '_') {
            token.value[i++] = current_char;
            next_char();
        }
        token.value[i] = '\0';
        

        if (strcmp(token.value, "int") == 0) token.type = T_INT;
        else if (strcmp(token.value, "return") == 0) token.type = T_RETURN;
        else token.type = T_IDENT;
        
        return token;
    }
    

    if (isdigit(current_char)) {
        int i = 0;
        while (isdigit(current_char)) {
            token.value[i++] = current_char;
            next_char();
        }
        token.value[i] = '\0';
        token.type = T_NUMBER;
        return token;
    }
    

    switch (current_char) {
        case '+': token.type = T_PLUS; break;
        case '-': token.type = T_MINUS; break;
        case '*': token.type = T_MULT; break;
        case '/': token.type = T_DIV; break;
        case '=': token.type = T_ASSIGN; break;
        case ';': token.type = T_SEMICOLON; break;
        case '(': token.type = T_LPAREN; break;
        case ')': token.type = T_RPAREN; break;
        case '{': token.type = T_LBRACE; break;
        case '}': token.type = T_RBRACE; break;
        default: token.type = T_UNKNOWN; break;
    }
    
    next_char();
    return token;
}
