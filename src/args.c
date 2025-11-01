#include "fcc.h"

void fcc_print_help() {
    printf("Usage: fcc [options] file...\n");
    printf("Options:\n");
    printf("  -c         Compile to object file only\n");
    printf("  -S         Compile to assembly only\n");
    printf("  -o <file>  Place output into <file>\n");
    printf("  -v         Verbose output\n");
    printf("  -g         Generate debug information\n");
    printf("  --help     Show this help\n");
}

void fcc_parse_args(int argc, char *argv[], FCC_Config *config) {
    int has_output_file = 0;
    
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-c") == 0) {
                config->compile_only = 1;
            }
            else if (strcmp(argv[i], "-S") == 0) {
                config->assemble_only = 1;
            }
            else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
                strcpy(config->output_file, argv[++i]);
                has_output_file = 1;
            }
            else if (strcmp(argv[i], "-v") == 0) {
                config->verbose = 1;
            }
            else if (strcmp(argv[i], "-g") == 0) {
                config->debug = 1;
            }
            else if (strcmp(argv[i], "--help") == 0) {
                fcc_print_help();
                exit(0);
            }
        } else {
            strcpy(config->input_files[config->input_count++], argv[i]);
        }
    }
    
    
    if (!has_output_file) {
        strcpy(config->output_file, "a.out");
    }
}
