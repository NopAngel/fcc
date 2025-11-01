#include "fcc.h"

// Versión de FCC
#define FCC_VERSION "0.1.0"
#define FCC_AUTHOR "The FCC Team"

// Banner chido del compilador
void fcc_print_banner() {
    printf("╔══════════════════════════════════════╗\n");
    printf("║         FCC - Free C Compiler        ║\n");
    printf("║             M I T LICENSE            ║\n", FCC_VERSION);
    printf("╚══════════════════════════════════════╝\n");
}

// Info de versión
void fcc_print_version() {
    printf("FCC (Free C Compiler) %s\n", FCC_VERSION);
    printf("Copyright (c) 2024 %s\n", FCC_AUTHOR);
    printf("This is free software; see the source for copying conditions LICENSE MIT.\n");
}

// Manejo de errores
void fcc_print_error(const char* message, const char* details) {
    printf("fcc: error: %s", message);
    if (details) printf(" '%s'", details);
    printf("\n");
}

void fcc_print_warning(const char* message) {
    printf("fcc: warning: %s\n", message);
}


int fcc_is_c_file(const char* filename) {
    const char* dot = strrchr(filename, '.');
    return dot && !strcmp(dot, ".c");
}


int fcc_process_input_files(FCC_Config* config) {
    for (int i = 0; i < config->input_count; i++) {
        if (!fcc_is_c_file(config->input_files[i])) {
            fcc_print_warning("file does not have .c extension");
        }
        
        
        int exists = access(config->input_files[i], F_OK) == 0;
        if (!exists) {
            fcc_print_error("cannot open input file", config->input_files[i]);
            return 0;
        }
        
        if (config->verbose) {
            printf("fcc: input: %s", config->input_files[i]);
            if (config->compile_only) printf(" -> [object file]");
            else if (config->assemble_only) printf(" -> [assembly]");
            else printf(" -> [executable]");
            printf("\n");
        }
    }
    return 1;
}


int main(int argc, char* argv[]) {

    if (argc > 1) {
        fcc_print_banner();
    }
    
    FCC_Config config = {0};
    

    strcpy(config.output_file, "a.out");
    config.optimize = 0;
    config.input_count = 0;
    

    fcc_parse_args(argc, argv, &config);
    
    if (config.input_count == 0) {
        if (argc == 1) {
            fcc_print_help();
        } else {
            fcc_print_error("no input files", NULL);
        }
        return 1;
    }
    

    if (!fcc_process_input_files(&config)) {
        return 1;
    }
    

    if (config.verbose) {
        printf("fcc: configuration:\n");
        printf("  Input files: %d\n", config.input_count);
        for (int i = 0; i < config.input_count; i++) {
            printf("    - %s\n", config.input_files[i]);
        }
        printf("  Output: %s\n", config.output_file);
        printf("  Mode: %s\n", 
               config.compile_only ? "compile only (-c)" :
               config.assemble_only ? "assembly only (-S)" : "full compilation");
        printf("  Debug: %s\n", config.debug ? "yes (-g)" : "no");
        printf("  Optimize: -O%d\n", config.optimize);
        printf("  Starting compilation...\n\n");
    }
    
    // COMPILE!
    int result = fcc_compile(&config);
    
    //show final res
    if (result) {
        if (config.verbose) {
            printf("\nfcc: ✅ compilation completed successfully!\n");
            if (!config.compile_only && !config.assemble_only) {
                printf("fcc: executable '%s' is ready to run! 🚀\n", config.output_file);
            }
        }
    } else {
        printf("\nfcc: ❌ compilation failed!\n");
        return 1;
    }
    
    return 0;
}
