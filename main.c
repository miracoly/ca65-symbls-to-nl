#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH_MAX 1024

static void print_help(void) {
    printf(
            "Convert cc65 label file into fceux namelist *.nl file.\n"
            "\tUsage:\n"
            "\t\tca65-symbls-to-nl -f input_file\n"
            "\tOptions:\n"
            "\t\t-f, --file\t\tConvert file.\n"
            "\t\t-h, --help\t\tShow this help text.\n"
            "\n"
    );
}

typedef void consume_file(FILE* file);

static void do_with_file(const char file_name[static 1], consume_file* consumer) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Could not open file '%s'.", file_name);
        exit(EXIT_FAILURE);
    }

    consumer(file);
    fclose(file);
}

static void convert_file(FILE* file) {
    printf("Converting file...\n");
    unsigned int total = 0;
    char line[LINE_LENGTH_MAX] = {0};

    while (fgets(line, LINE_LENGTH_MAX, file)) {
        total += 1;
    }
    printf("%u\n", total);
}

static void handle_cmd_line_args(int argc, char* const* argv) {
    const char* option = argv[1];

    if (argc <= 1 || !strcmp(option, "--help") || (!strcmp(option, "-h"))) print_help();
    if (!strcmp(option, "--file") || (!strcmp(option, "-f"))) {
        const char* file_name = argv[2];
        if (!file_name) {
            printf("Error: No file name provided after option %s.\n", option);
            exit(EXIT_FAILURE);
        }
        do_with_file(file_name, convert_file);
    } else {
        printf("Unknown option.\nUse --help for more info.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[argc + 1]) {
    handle_cmd_line_args(argc, argv);
    return EXIT_SUCCESS;
}
