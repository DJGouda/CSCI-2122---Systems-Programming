#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "xis.h"
#include "xcpu.h"
#include "xmem.h"

int main(int argc, char **argv) {
    // Validate command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <cycles> <program_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse and validate cycles
    char *endptr;
    long max_cycles = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || max_cycles < 0) {
        fprintf(stderr, "Error: cycles must be a non-negative integer\n");
        return EXIT_FAILURE;
    }

    // Initialize memory system (64KB)
    xmem_init(65536);
    uint8_t *memory = xmem_get_memory();

    // Open program file
    FILE *program_file = fopen(argv[2], "rb");
    if (!program_file) {
        perror("Error opening program file");
        return EXIT_FAILURE;
    }

    // Determine file size
    struct stat st;
    if (fstat(fileno(program_file), &st) != 0) {
        perror("Error getting file size");
        fclose(program_file);
        return EXIT_FAILURE;
    }

    // Verify file size
    if (st.st_size > 65536) {
        fprintf(stderr, "Error: program file exceeds 64KB memory limit\n");
        fclose(program_file);
        return EXIT_FAILURE;
    }

    // Load program into memory
    size_t bytes_read = fread(memory, 1, st.st_size, program_file);
    fclose(program_file);

    if (bytes_read != (size_t)st.st_size) {
        fprintf(stderr, "Error: failed to read complete program file\n");
        return EXIT_FAILURE;
    }

    // Initialize CPU context
    xcpu cpu;
    memset(&cpu, 0, sizeof(xcpu));  // Clear all registers and state

    // Execution loop
    long cycles = 0;
    while ((max_cycles == 0 || cycles < max_cycles)) {
        if (!xcpu_execute(&cpu)) {
            break;  // Execution failed or program halted
        }
        cycles++;
    }

    return EXIT_SUCCESS;
}