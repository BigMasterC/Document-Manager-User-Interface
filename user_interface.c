/*
    Name: Chibundu Onwuegbule
    UID: 119312827
    Directory ID: conwueg1
*/

#include "document.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define MAX_LINE_LEN 1024

/*HELPER FUNCTIONS:*/
char *extract_target(char *function_name, char *target) {
    char *start_quote, *end_quote;

    /*looking for a double quote in the string passed in through @param "function_name"*/
    start_quote = strstr(function_name, "\"");
    /*if we can find the first double quote...*/
    if (start_quote != NULL) {
        /*see if we can find its pairing!*/
        end_quote = strstr(start_quote + 1, "\"");

        if (end_quote != NULL) {
            size_t length = end_quote - start_quote;
            strncpy(target, start_quote + 1, length);
            target[end_quote - (start_quote + 1)] = '\0';

            return target;
        }
    }
    return NULL;
}

/* Function to handle # of command line arguments */
/*FIRST 2 PARAGRAPHS*/
void handle_command_line_arguments(int argc, char *argv[], FILE **input_file) {
    /* Handling argument count and assign the input file accordingly */

    switch (argc) {

    case 1:

        *input_file = stdin;
        /* Reading from standard input (user typing the stuff that will be inputted) */

        printf("> "); /*getting ready to recieve FIRST line of user input*/

        break;
    case 2:

        /*opening the file that has a predefined list of commands*/
        *input_file = fopen(argv[1], "r");

        /*If we fail to open the file...*/
        if (*input_file == NULL) {
            fprintf(stderr, "%s cannot be opened.\n", argv[1]);
            exit(EX_OSERR);
        }

        break;

    default:
        /* Invalid number of arguments */
        fprintf(stderr, "Usage: user_interface\n");
        fprintf(stderr, "Usage: user_interface <filename>\n");
        exit(EX_USAGE);
        break;
    }
}

/* Function to execute commands based on input */
int execute_command(Document *doc, const char *command) {
    /* Validate and execute the command provided */

    char function_name[MAX_STR_SIZE + 1], extra_info[MAX_STR_SIZE + 1],
        line_content[MAX_STR_SIZE + 1], file_name[MAX_STR_SIZE + 1];
    char target[MAX_STR_SIZE + 1], *target_string, replacement[MAX_STR_SIZE + 1],
        *first_quote, *second_quote, *third_quote, *fourth_quote;

    int paragraph_number, values_read, line_num, done = 0, terminate_program = -1;

    /* Extract the command keyword (guarentees us that there will at least be a function_name) */
    if (sscanf(command, "%s", function_name) != 1) {
        /*extracting the first word from the "command" string and storing it in our buffer array
        "function nam...returns the # of commands read so it SHOULD equal "1"*/
        printf("Invalid Command\n");
        return done;
    }

    /*NOTE: there will always be ONE function name in that buffer at a time so we can use
    "strcmp" :] */

    /* Based on the command keyword, execute the appropriate action */
    if (strcmp(function_name, "add_paragraph_after") == 0) {

        values_read = sscanf(command, "%s %d %s", function_name, &paragraph_number, extra_info);

        if (values_read == 2 && paragraph_number >= 0) {
            /*(executes the function btw)...if the function cannot be
            executed...*/
            if (add_paragraph_after(doc, paragraph_number) == FAILURE) {
                printf("add_paragraph_after failed\n");
            }

            return done;

        } else {

            printf("Invalid Command\n");

            return done;
        }
    } else if (strcmp(function_name, "add_line_after") == 0) {

        values_read = sscanf(command, "%s %d %d %s", function_name, &paragraph_number,
                             &line_num, line_content);

        if (values_read == 4 && paragraph_number > 0 && line_num >= 0 && strchr(command, '*') != NULL) {
            /*copying the content following the '*'*/
            strcpy(line_content, strchr(command, '*') + 1);

            if (add_line_after(doc, paragraph_number, line_num, line_content) == FAILURE) {
                printf("add_line_after failed\n");
            }

            return done;
        } else {

            printf("Invalid Command\n");

            return done;
        }
    } else if (strcmp(function_name, "print_document") == 0) {

        values_read = sscanf(command, "%s %s", function_name, extra_info);

        if (values_read == 1) {

            /*if (strlen(command) > strlen("print_document")) {
                printf("Invalid Command\n");
                return done;
            }*/

            if (print_document(doc) == FAILURE) {
                printf("print_document failed\n");
            }

            /* Execute the print_document command */
            /*print_document(doc); could possibly be due to the white space characters in front of "print_document"*/
            return done;
        } else {

            printf("Invalid Command\n");

            return done;
        }

    } else if (strcmp(function_name, "quit") == 0 || strcmp(function_name, "exit") == 0) {

        /*if (strlen(command) > strlen("quit") || strlen(command) > strlen("exit")) {
            printf("Invalid Command\n");
            return done;
        }*/

        values_read = sscanf(command, "%s %s", function_name, extra_info);

        if (values_read == 1) {

            return terminate_program;

        } else {

            printf("Invalid Command\n");

            return done;
        }

        /*if the user gave a file...fclose()*/
        /*if it's stdin... (do this in main btw) return */

        /*TO-DO: exit the user_interface...maybe by closing the file? Or returning?*/
    } else if (strcmp(function_name, "append_line") == 0) {

        values_read = sscanf(command, "%s %d %s", function_name, &paragraph_number, line_content);

        if (values_read == 3 && paragraph_number > 0 && strchr(command, '*') != NULL) {
            /*copying the content following the '*'*/
            strcpy(line_content, strchr(command, '*') + 1);

            if (append_line(doc, paragraph_number, line_content) == FAILURE) {
                printf("append_line failed\n");
            }
            return done;
        } else {

            printf("Invalid Command\n");

            return done;
        }
    } else if (strcmp(function_name, "remove_line") == 0) {

        values_read = sscanf(command, "%s %d %d %s", function_name, &paragraph_number, &line_num, extra_info);

        if (values_read == 3 && paragraph_number > 0 && line_num > 0) {

            if (remove_line(doc, paragraph_number, line_num) == FAILURE) {
                printf("remove_line failed\n");
            }
            return done;
        } else {

            printf("Invalid Command\n");

            return done;
        }
    } else if (strcmp(function_name, "load_file") == 0) {

        values_read = sscanf(command, "%s %s %s", function_name, file_name, extra_info);

        if (values_read == 2) {

            if (load_file(doc, file_name) == FAILURE) {
                printf("load_file failed\n");
            }
            return done;
        } else {

            printf("Invalid Command\n");

            return done;
        }
    } else if (strcmp(function_name, "replace_text") == 0) {

        values_read = sscanf(command, "%s %s %s", function_name, target, replacement);
        first_quote = strstr(command, "\"");

        /* Extract the necessary strings between the quotes */
        if (values_read == 3 && first_quote != NULL) {
            second_quote = strstr(first_quote + 1, "\"");
            third_quote = strstr(second_quote + 1, "\"");
            fourth_quote = strstr(third_quote + 1, "\"");

            if (second_quote != NULL && third_quote != NULL && fourth_quote != NULL) {
                strncpy(target, first_quote + 1, second_quote - first_quote - 1);
                target[second_quote - first_quote - 1] = '\0';

                strncpy(replacement, third_quote + 1, fourth_quote - third_quote - 1);
                replacement[fourth_quote - third_quote - 1] = '\0';

                /* If replace_text fails, print an error message */
                if (replace_text(doc, target, replacement) == FAILURE) {
                    printf("replace_text failed\n");
                }
                return done;
            }
            return done;
        } else {
            printf("Invalid Command\n");
            return done;
        }

    } else if (strcmp(function_name, "highlight_text") == 0) {

        values_read = sscanf(command, "%s %s", function_name, target);
        first_quote = strstr(command, "\"");

        if (values_read == 2 && first_quote != NULL) {
            if ((target_string = extract_target(first_quote, target)) != NULL) {
                highlight_text(doc, target_string);
                return done;
            }
        } else {
            printf("Invalid Command\n");
            return done;
        }
    } else if (strcmp(function_name, "remove_text") == 0) {

        values_read = sscanf(command, "%s %s", function_name, target);
        first_quote = strstr(command, "\"");

        if (values_read == 2 && first_quote != NULL) {
            if ((target_string = extract_target(first_quote, target)) != NULL) {
                remove_text(doc, target_string);
                return done;
            }
        } else {
            printf("Invalid Command\n");
            return done;
        }
    } else if (strcmp(function_name, "save_document") == 0) {

        values_read = sscanf(command, "%s %s %s", function_name, file_name, extra_info);

        if (values_read == 2) {
            if (save_document(doc, file_name) == FAILURE) {
                printf("save_document failed\n");
            }
            return done;
        } else {

            printf("Invalid Command\n");

            return done;
        }
    } else if (strcmp(function_name, "reset_document") == 0) {

        values_read = sscanf(command, "%s %s", function_name, extra_info);

        if (values_read == 1) {
            reset_document(doc);
            return done;
        } else {

            printf("Invalid Command\n");

            return done;
        }
    } else {

        printf("Invalid Command\n");

        return done;
    }
}

int main(int argc, char *argv[]) {
    Document doc;
    char line[MAX_LINE_LEN + 1], character, proceeding_string[MAX_LINE_LEN + 1], *replace;
    FILE *input_file;
    const char *main_document = "main_document";
    int exit_code;
    int is_blank;
    size_t complement_len;

    /* Initialize the document with the name "main_document"*/
    if (init_document(&doc, main_document) == FAILURE) {

        printf("Failed to initialize \"main_document\"\n"); /*double check if I have to print out smth*/

    } else {
        /* Handle command line arguments */
        handle_command_line_arguments(argc, argv, &input_file);

        /* Loop to read and execute commands */
        /*while fgets() input from the "input_file()..."*/
        while (fgets(line, MAX_STR_SIZE + 1, input_file)) {

            is_blank = sscanf(line, " %c", &character);

            sscanf(line, " %c%s", &character, proceeding_string); /* looking for comments */

            replace = strstr(line, "\n");
            /* getting rid of the new line character as "fgets()" also reads in the new line character */
            if (replace != NULL) {
                replace[0] = '\0'; /*replacing the pointer to the new line char with a null terminator*/
            }

            /*if the line we're dealing with isn't a comment AND it isn't a new line...*/
            if (character != '#' && is_blank != EOF) { /*11/17 (ASK TA: should I do this?)*/
                /* Process the command */
                exit_code = execute_command(&doc, line);
                /*could change master function to return something that will help me break out
                of this loop*/
            }

            if (exit_code == -1) {
                break;
            }

            if (argc == 1) {
                printf("> "); /*always print this line to*/
            }
        }
    }

    /* Close the input file...bc...good practice ;]*/
    if (input_file != stdin) {

        fclose(input_file); /*update*/
    }

    exit(EXIT_SUCCESS);
}
