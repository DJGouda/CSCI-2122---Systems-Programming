// @Duren Gouda
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("error opening file");
        return 1;
    }

    // littke endian format
    uint32_t offset = 0;
    uint32_t value;

    printf("%u\n", offset);

    
    if (fseek(file, offset, SEEK_SET) != 0) { // read first value at offset 0
        perror("error seeking in file");
        fclose(file);
        return 1;
    }

    if (fread(&value, sizeof(uint32_t), 1, file) != 1) {
        perror("error reading from file");
        fclose(file);
        return 1;
    }

    // loop till read a 0 value
    while (value != 0) {
        offset = value;
        printf("%u\n", offset);

        // new offset
        if (fseek(file, offset, SEEK_SET) != 0) {
            perror("error seeking in file");
            fclose(file);
            return 1;
        }

        // read next value
        if (fread(&value, sizeof(uint32_t), 1, file) != 1) {
            perror("error reading from file");
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
