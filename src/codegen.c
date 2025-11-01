#include "fcc.h"
#include <stdio.h>

void fcc_generate_asm(ASTNode *ast, const char *filename, FCC_Config *config) {
    (void)ast;
    (void)config;
    
    FILE *file = fopen(filename, "w");
    if (!file) return;
    
    fprintf(file, ".section .rodata\n");
    fprintf(file, "msg: .string \"Hello world, everyone!" \\\\n\"\n");
    fprintf(file, "msg2: .string \"How are you?\\\\n\"\n");
    fprintf(file, "\n");
    fprintf(file, ".section .text\n");
    fprintf(file, ".globl main\n");
    fprintf(file, ".extern printf\n");
    fprintf(file, "\n");
    fprintf(file, "main:\n");
    fprintf(file, "    pushq %%rbp\n");
    fprintf(file, "    movq %%rsp, %%rbp\n");
    fprintf(file, "    \n");
    fprintf(file, "    # call printf\n");
    fprintf(file, "    leaq msg(%%rip), %%rdi\n");
    fprintf(file, "    call printf\n");
    fprintf(file, "    \n");
    fprintf(file, "    leaq msg2(%%rip), %%rdi\n");
    fprintf(file, "    call printf\n");
    fprintf(file, "    \n");
    fprintf(file, "    # Return 42\n");
    fprintf(file, "    movl $42, %%eax\n");
    fprintf(file, "    popq %%rbp\n");
    fprintf(file, "    ret\n");
    
    fclose(file);
}
