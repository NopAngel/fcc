#include "fcc.h"
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void fcc_get_basename(const char* path, char* result) {
    char base[256];
    strcpy(base, path);
    
    char* file_name = basename(base);
    char* dot = strrchr(file_name, '.');
    if (dot && strcmp(dot, ".c") == 0) {
        *dot = '\0';
    }
    strcpy(result, file_name);
}


int file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

int fcc_compile(FCC_Config *config) {
    if (config->verbose) {
        printf("fcc: compiling %s -> %s\n", config->input_files[0], config->output_file);
    }
    

    if (!file_exists(config->input_files[0])) {
        printf("fcc: error: input file '%s' not found\n", config->input_files[0]);
        return 0;
    }
    
    char base_name[256];
    fcc_get_basename(config->input_files[0], base_name);
    

    char asm_file[256];
    
    if (config->assemble_only) {
        strcpy(asm_file, config->output_file);
    } else {
        sprintf(asm_file, "fcc_temp_%d.s", getpid());
    }
    
    if (config->verbose) {
        printf("fcc: generating assembly: %s\n", asm_file);
    }
    
    // assembly
    fcc_generate_asm(NULL, asm_file, config);
    
    if (config->assemble_only) {
        if (config->verbose) {
            printf("fcc: assembly saved to %s\n", asm_file);
        }
        return 1;
    }
    

    if (config->verbose) {
        printf("fcc: assembling %s\n", asm_file);
    }
    
    char obj_file[256];
    if (config->compile_only) {
        strcpy(obj_file, config->output_file);
    } else {
        sprintf(obj_file, "fcc_temp_%d.o", getpid());
    }
    
    char cmd[512];
    sprintf(cmd, "as --64 %s -o %s", asm_file, obj_file);
    
    if (system(cmd) != 0) {
        printf("fcc: error: assembly failed\n");
        remove(asm_file);
        return 0;
    }
    

    remove(asm_file);
    
    if (config->compile_only) {
        if (config->verbose) {
            printf("fcc: object file saved to %s\n", obj_file);
        }
        return 1;
    }
    

    if (config->verbose) {
        printf("fcc: linking -> %s\n", config->output_file);
    }
    
    sprintf(cmd, "gcc -no-pie %s -o %s", obj_file, config->output_file);
    
    if (system(cmd) != 0) {
        printf("fcc: error: linking failed\n");
        remove(obj_file);
        return 0;
    }
    
    remove(obj_file);
    
    if (config->verbose) {
        printf("fcc: executable '%s' created successfully\n", config->output_file);
    }
    
    return 1;
}
