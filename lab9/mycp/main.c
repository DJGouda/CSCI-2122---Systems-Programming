#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) { // examples taken from the lab materials provided!!
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    FILE *src = NULL, *dst = NULL;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    
    src = fopen(argv[1], "rb"); // open the source file
    if (src == NULL) {
        perror("error opening source file");
        return 1;
    }

    
    dst = fopen(argv[2], "wb"); // open the destination file, which may be cvreated
    if (dst == NULL) {
        perror("error opening destination file");
        fclose(src);
        return 1;
    }

    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) { // to copy the file contents
        if (fwrite(buffer, 1, bytes_read, dst) != bytes_read) {
            perror("error writing to destination file");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    
    if (ferror(src)) { // for read errors
        perror("error reading source file");
        fclose(src);
        fclose(dst);
        return 1;
    }

    fclose(src);
    fclose(dst);

    return 0;
}