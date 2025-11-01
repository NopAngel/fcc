#ifndef FCC_H
#define FCC_H


#include <unistd.h>   // access, getpid
#include <stdio.h>    // printf, NULL
#include <stdlib.h>   // system
#include <string.h>   // strcpy, strcmp, strrchr
// confg
typedef struct {
    int verbose;
    int debug;
    int optimize;
    char output_file[256];
    char input_files[10][256];
    int input_count;
    int compile_only;
    int assemble_only;
    int preprocess_only;
} FCC_Config;

// Tokens
typedef enum {
    T_INT, T_FLOAT, T_CHAR, T_IF, T_ELSE, T_WHILE, T_RETURN,
    T_IDENT, T_NUMBER, T_STRING, T_PLUS, T_MINUS, T_MULT, T_DIV,
    T_ASSIGN, T_EQ, T_NE, T_LT, T_GT, T_SEMICOLON, T_COMMA,
    T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE, T_EOF, T_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[256];
    int line;
} Token;

typedef struct ASTNode {
    char type[32];
    char value[128];
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
} ASTNode;

// fncs
void fcc_parse_args(int argc, char *argv[], FCC_Config *config);
int fcc_compile(FCC_Config *config);
void fcc_print_help();
void fcc_generate_asm(ASTNode *ast, const char *filename, FCC_Config *config);
Token fcc_next_token();

#endif
