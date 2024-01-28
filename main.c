#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* file = fopen("./file", "r");
    if (!file) {
        perror("Could not open file 'file'.");
        return EXIT_FAILURE;
    }

    printf("Success\n");

    fclose(file);
    return EXIT_SUCCESS;
}
