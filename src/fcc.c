#include "fcc.h"

int main(int argc, char *argv[]) {
    printf("FCC - Free C Compiler v0.1\n");
    
    FCC_Config config = {0};
    strcpy(config.output_file, "a.out");
    
    fcc_parse_args(argc, argv, &config);
    
    if (config.input_count == 0) {
        printf("fcc: error: no input files\n");
        return 1;
    }
    
    if (!fcc_compile(&config)) {
        printf("fcc: compilation failed\n");
        return 1;
    }
    
    printf("fcc: compilation successful! 🎉\n");
    return 0;
}
