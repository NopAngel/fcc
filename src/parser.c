#include "fcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Token current_token;
static int has_errors = 0;

static void next_token() {
    current_token = fcc_next_token();
}

static void expect(TokenType expected, const char *msg) {
    if (current_token.type != expected) {
        printf("Error (line %d): Expected %s, got %s\n", 
               current_token.line, msg, current_token.value);
        has_errors = 1;
    }
    next_token();
}

ASTNode* parse_expression();
ASTNode* parse_term();
ASTNode* parse_factor();

ASTNode* create_node(const char *type, const char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    strcpy(node->type, type);
    if (value) strcpy(node->value, value);
    node->left = node->right = node->next = NULL;
    return node;
}

ASTNode* parse_factor() {
    ASTNode *node = NULL;
    
    if (current_token.type == T_NUMBER) {
        node = create_node("number", current_token.value);
        next_token();
    } else if (current_token.type == T_IDENT) {
        node = create_node("variable", current_token.value);
        next_token();
    } else if (current_token.type == T_LPAREN) {
        next_token();
        node = parse_expression();
        expect(T_RPAREN, ")");
    }
    
    return node;
}

ASTNode* parse_term() {
    ASTNode *node = parse_factor();
    
    while (current_token.type == T_MULT || current_token.type == T_DIV) {
        ASTNode *op = create_node("operator", 
            current_token.type == T_MULT ? "*" : "/");
        next_token();
        op->left = node;
        op->right = parse_factor();
        node = op;
    }
    
    return node;
}

ASTNode* parse_expression() {
    ASTNode *node = parse_term();
    
    while (current_token.type == T_PLUS || current_token.type == T_MINUS) {
        ASTNode *op = create_node("operator", 
            current_token.type == T_PLUS ? "+" : "-");
        next_token();
        op->left = node;
        op->right = parse_term();
        node = op;
    }
    
    return node;
}

ASTNode* parse_return_statement() {
    ASTNode *node = create_node("return", NULL);
    next_token(); // skip 'return'
    
    node->left = parse_expression();
    expect(T_SEMICOLON, ";");
    
    return node;
}

ASTNode* parse_declaration() {
    expect(T_INT, "int");
    
    ASTNode *decl = create_node("declaration", current_token.value);
    expect(T_IDENT, "identifier");
    
    if (current_token.type == T_ASSIGN) {
        next_token(); // skip '='
        ASTNode *assign = create_node("assignment", decl->value);
        assign->left = parse_expression();
        decl->next = assign;
    }
    
    expect(T_SEMICOLON, ";");
    return decl;
}

ASTNode* parse_statement() {
    if (current_token.type == T_RETURN) {
        return parse_return_statement();
    } else if (current_token.type == T_INT) {
        return parse_declaration();
    }
    return NULL;
}

ASTNode* parse_function() {
    expect(T_INT, "int");
    expect(T_IDENT, "function name");
    expect(T_LPAREN, "(");
    expect(T_RPAREN, ")");
    expect(T_LBRACE, "{");
    
    ASTNode *func = create_node("function", "main");
    ASTNode *last_stmt = NULL;
    
    while (current_token.type != T_RBRACE && current_token.type != T_EOF) {
        ASTNode *stmt = parse_statement();
        if (stmt) {
            if (last_stmt == NULL) {
                func->left = stmt;
                last_stmt = stmt;
            } else {
                last_stmt->next = stmt;
                last_stmt = stmt;
            }
        } else {
            next_token(); // skip unknown tokens
        }
    }
    
    expect(T_RBRACE, "}");
    return func;
}

ASTNode* fcc_parse(const char *filename) {
    fcc_init_lexer(filename);
    next_token();
    
    ASTNode *ast = parse_function();
    
    fcc_close_lexer();
    return has_errors ? NULL : ast;
}
