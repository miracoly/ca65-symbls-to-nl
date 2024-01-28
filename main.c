#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH_MAX 1024
#define OUTPUT_FILE_ENDING ".nl"

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

typedef void consume_file(FILE* file, const char file_name[static 1]);

static void do_with_file(const char file_name[static 1], consume_file* consumer) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "Could not open file '%s'.", file_name);
        exit(EXIT_FAILURE);
    }

    consumer(file, file_name);
    fclose(file);
}

static void handle_line_error(const char* line) {
    fprintf(stderr, "Error: input line is in wrong format. Line: %s\n", line);
    exit(EXIT_FAILURE);
}

static void convert_line(char line[LINE_LENGTH_MAX], FILE* output) {
    char line_cpy[LINE_LENGTH_MAX] = {0};
    strcpy(line_cpy, line);
    strtok(line_cpy, " ");
    char* sub_str = strtok((void*) 0, " ");

    if (sub_str && strlen(sub_str) > 2) {
        sub_str += 2;
        fputc('$', output);
        fputs(sub_str, output);
    } else {
        handle_line_error(line);
    }

    sub_str = strtok((void*) 0, "\n");
    if (sub_str && strlen(sub_str) > 1) {
        sub_str++;
        fputc('#', output);
        fputs(sub_str, output);
    } else {
        handle_line_error(line);
    }

    fputs("#\n", output);
}

static void convert_file(FILE* file, const char file_name[static 1]) {
    printf("Converting file %s ...\n", file_name);

    char output_name[strlen(file_name) + strlen(OUTPUT_FILE_ENDING) + 1];
    strcpy(output_name, file_name);
    strcat(output_name, OUTPUT_FILE_ENDING);

    FILE* output = fopen(output_name, "w");
    char line[LINE_LENGTH_MAX] = {0};
    while (fgets(line, LINE_LENGTH_MAX, file)) {
        convert_line(line, output);
    }

    printf("Output written to %s\n", output_name);
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
