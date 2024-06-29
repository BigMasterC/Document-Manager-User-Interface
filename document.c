/*
    Name: Chibundu Onwuegbule
    UID: 119312827
    Directory ID: conwueg1
*/

#include "document.h" /*Assuming that this is a user written file*/
#include <ctype.h>    /*Need to include for the "isspace()" function*/
#include <stdio.h>
#include <string.h>

/*NOTE TO SELF: "*doc" is a Pointer to an INSTANCE of "struct Document."

Also, we're able to use the aliased struct name because of "typedef" keyword
in header file*/
/*Initializes the document, setting it as empty and assigning the provided name.
Failure if doc or name is NULL or the name exceeds the maximum length.*/
int init_document(Document *doc, const char *name) {

    if (doc == NULL || name == NULL || strlen(name) > MAX_STR_SIZE) {
        return FAILURE;
    }

    doc->number_of_paragraphs = 0; /*Initializes an empty document*/
    strcpy(doc->name, name);
    /*Copies over the name provided as an argument as a name for the document
    (let's pretend its a Word Doc bc MS Word>>)*/

    return SUCCESS;
}

/*Basically removes all the paragraphs within the Document*/
int reset_document(Document *doc) {
    /*ASK: is there a way to make a helper variable for this (below)?*/
    if (doc == NULL) {
        return FAILURE;
    }

    doc->number_of_paragraphs = 0;

    return SUCCESS;
}

/*Prints the contents of the document:
 * Name
 * Number of Paragraph (Proceeded by the actual paragraph)
 * Actual Paragraph (Preceeded by its number)
 */
int print_document(Document *doc) {

    int i = 0, j = 0;

    if (doc == NULL) {
        return FAILURE;
    }

    printf("Document name: \"%s\"\n", doc->name);
    printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);

    if (doc->number_of_paragraphs != 0) {
        /*Check outer loop if anything pops up*/
        for (i = 0; i < doc->number_of_paragraphs; i++) {
            if (doc->paragraphs[i].number_of_lines != 0) {
                for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
                    printf("%s\n", doc->paragraphs[i].lines[j]);
                }
                if (i < doc->number_of_paragraphs - 1) {
                    printf("\n"); /*Print a new line*/
                }
            }

            /*After you are done printing all the lines within a paragraph...
            print a new line!*/
        }
    }

    return SUCCESS;
}

/*Adds a paragraph after the specified paragraph number*/
int add_paragraph_after(Document *doc, int paragraph_number) {

    int i = 0;

    if (doc == NULL || paragraph_number < 0 || doc->number_of_paragraphs >= MAX_PARAGRAPHS ||
        paragraph_number > doc->number_of_paragraphs) {
        return FAILURE;
    }

    /* To avoid overwriting existing paragraphs...we're traversing backwards
    and moving the paragraphs in the array of paragraphs down one index.
    We'll keep going as long as the index is greater than the paragraph number
    that we have to add on after. */

    /* check if you need to insert an element */

    for (i = doc->number_of_paragraphs; i > paragraph_number; i--) {
        doc->paragraphs[i] = doc->paragraphs[i - 1];
    }

    if (doc->number_of_paragraphs == 0) {
        doc->paragraphs[0].number_of_lines = 0;
    } else {
        /*After we've made room for the paragraph, we can now add it*/
        doc->paragraphs[paragraph_number].number_of_lines = 0;
        /*Added a paragraph with no lines (which was initially just trash)*/
    }

    /*Increment the number of paragraphs in the document*/
    doc->number_of_paragraphs++;

    return SUCCESS;
}

/*Adds a new line after a specified line or at the beginning of a paragraph.
Failure if doc is NULL, exceeds paragraph or line limits, or new_line is NULL.*/
int add_line_after(Document *doc, int paragraph_number, int line_number, const char *new_line) {

    int i = 0, num_of_paragraph_lines;

    /*Double check the conditions*/
    if (doc == NULL || paragraph_number <= 0 || line_number < 0 || doc->paragraphs[paragraph_number - 1].number_of_lines >= MAX_PARAGRAPH_LINES || paragraph_number > doc->number_of_paragraphs || line_number > doc->paragraphs[paragraph_number - 1].number_of_lines || new_line == NULL) {
        return FAILURE;
    }

    num_of_paragraph_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
    /*Starting from the total number of paragraph lines and moving the index 0*/
    for (i = num_of_paragraph_lines; i > line_number; i--) {
        strcpy(doc->paragraphs[paragraph_number - 1].lines[i], doc->paragraphs[paragraph_number - 1].lines[i - 1]);
    }
    if (doc->paragraphs[paragraph_number - 1].number_of_lines == 0)
        strcpy(doc->paragraphs[paragraph_number - 1].lines[0], new_line);
    else
        strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number], new_line);
    doc->paragraphs[paragraph_number - 1].number_of_lines++;

    return SUCCESS;
}

/*Retrieves the number of lines in a paragraph. Failure for NULL doc,
NULL number_of_lines, or invalid paragraph number.*/
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines) {

    if (doc == NULL || paragraph_number < 0 || number_of_lines == NULL || paragraph_number >= doc->number_of_paragraphs) {
        return FAILURE;
    }

    *number_of_lines = doc->paragraphs[paragraph_number].number_of_lines;

    /*QUESTION: should I also return "number_of_lines"?*/
    return SUCCESS;
}

/*Appends a line to a specified paragraph. Similar to add_line_after, with the same failure conditions.*/
int append_line(Document *doc, int paragraph_number, const char *new_line) {

    int result;

    result = add_line_after(doc, paragraph_number, doc->paragraphs[paragraph_number - 1].number_of_lines, new_line);

    return result;
}

/*Removes a specified line from a paragraph. Failure for NULL doc, invalid paragraph number, or line_number.*/
int remove_line(Document *doc, int paragraph_number, int line_number) {

    int i = 0, num_of_paragraph_lines;

    if (doc == NULL || paragraph_number < 0 || paragraph_number > doc->number_of_paragraphs || line_number < 0 || line_number >= doc->paragraphs[paragraph_number - 1].number_of_lines) {
        return FAILURE;
    }

    num_of_paragraph_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;

    for (i = line_number - 1; i < num_of_paragraph_lines - 1; i++) {
        strcpy(doc->paragraphs[paragraph_number - 1].lines[i], doc->paragraphs[paragraph_number - 1].lines[i + 1]);
    }

    doc->paragraphs[paragraph_number - 1].number_of_lines--;

    return SUCCESS;
}

/*Takes in a set of data and uses it to create a structured representation
of a document. The document is then divided into paragraphs
(where each paragraph contains one or more lines of text)*/

/*@param data: contains lines of text (each line representing a portion of the document)
The function processes the data array and divides it into paragraphs. Paragraphs are seperated by
empty lines (lines with no text)*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines) {

    int i = 0, paragraph_num = 0;
    /*Starting at -1 to indicate the 1st paragraph*/

    if (doc == NULL || data == NULL || data_lines == 0) {
        return FAILURE;
    }

    add_paragraph_after(doc, paragraph_num);
    paragraph_num++;

    for (i = 0; i < data_lines; i++) {
        /*If line/string is empty (null byte)...increase the paragraph_num
        (indicating the number of paragraphs in the document)*/
        if (data[i][0] == '\0') {
            /*Add paragraph to indicate that we've added a paragraph to the document*/

            add_paragraph_after(doc, paragraph_num);
            paragraph_num++; /*Increment the paragraph number after finding an empty string*/

            /*If paragraph_num ever becomes greater or equal to the maximum
            amount of paragraphs alloted in the document...return failure (to load the document)*/
            if (paragraph_num >= MAX_PARAGRAPHS) {
                return FAILURE;
            }
        } else {
            /*If line is NOT empty...ADD IT TO THE CURRENT PARAGRAPH! :D*/
            /*Performs the function call and then checks the output*/
            if (add_line_after(doc, paragraph_num, doc->paragraphs[paragraph_num - 1].number_of_lines, data[i]) == FAILURE) {
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}

/*helper function to help me remove extra spaces :D*/
void remove_extra_spaces(char *str) {
    size_t len = strlen(str);
    size_t i, j = 0;
    int space_flag = 0;

    for (i = 0; i < len; i++) {
        if (isspace(str[i])) {
            if (!space_flag) {

                str[j++] = ' ';
                space_flag = 1;
            }
        } else {

            str[j++] = str[i];
            space_flag = 0;
        }
    }

    str[j] = '\0';

    while (j > 0 && isspace(str[j - 1])) {
        j--;
    }
    str[j] = '\0';
}

/*Replaces target text with replacement throughout the document. Failure if doc, target, or replacement are NULL.*/
int replace_text(Document *doc, const char *target, const char *replacement) {

    int i = 0, j = 0, num_of_replacements = 0, start, end;
    char *line, *pos, temp[MAX_STR_SIZE + 1], modified_target[MAX_STR_SIZE + 1];
    size_t target_len;

    if (doc == NULL || target == NULL || replacement == NULL) {
        return FAILURE;
    }

    /*successfully parses the first few spaces in the string*/
    while (isspace(*target)) {
        target++;
    }

    /*removing trailing spaces*/
    strcpy(modified_target, target);
    remove_extra_spaces(modified_target);

    for (i = 0; i < doc->number_of_paragraphs; i++) {
        for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
            line = doc->paragraphs[i].lines[j];

            while ((pos = strstr(line, modified_target)) != NULL) {
                start = pos - line;
                end = start + strlen(modified_target);

                /*skip multiple spaces when searching*/
                while (start > 0 && isspace(modified_target[start - 1])) {
                    start--;
                }

                strcpy(temp, line + end);
                strcpy(pos, replacement);
                strcat(line, temp);
                line = line + start + strlen(replacement);
                num_of_replacements++;
            }
        }
    }
    return SUCCESS;
}

/*Highlights the specified target text in the document. Fails if doc or target is NULL.*/
int highlight_text(Document *doc, const char *target) {
    char real_target[MAX_STR_SIZE + 1];

    strcpy(real_target, HIGHLIGHT_START_STR);
    strcat(real_target, target);
    strcat(real_target, HIGHLIGHT_END_STR);

    return replace_text(doc, target, real_target);
}

/*Removes each occurance of the target string from the document*/
int remove_text(Document *doc, const char *target) {
    return replace_text(doc, target, "");
}

/* NEEDS TESTING STILL!!: Loads data from a file into the document. */
/*ASK TA:...wait...how would I test this?*/
int load_file(Document *doc, const char *filename) {

    FILE *file;
    int paragraph_num = 0, i = 0;
    char line[MAX_STR_SIZE + 1]; /* Buffer for reading lines */

    if (doc == NULL || filename == NULL) {
        return FAILURE;
    }

    file = fopen(filename, "r");

    /* Opening file failed */
    if (file == NULL) {
        return FAILURE;
    }

    /*"by default the function adds a new paragraph"*/
    add_paragraph_after(doc, paragraph_num);
    paragraph_num++;

    /*while we are able to read lines from the file...*/
    while (fgets(line, sizeof(line), file) != NULL) {

        /*If the first character within the line is empty...then it's likely an empty line*/

        if (isspace(line[0])) { /* Checks if the line is empty or contains only spaces */

            /*If paragraph_num ever becomes greater or equal to the maximum
            amount of paragraphs alloted in the document...return SUCCESS (to load the file)*/
            if (paragraph_num >= MAX_PARAGRAPHS) {
                /* great practice to close the file you opened ;] */
                fclose(file);
                return FAILURE; /* Exceeding maximum allowed paragraphs */
                /*UPDATE: can I just do this? Can I return success instead(it allows me to print out only 15 paragraphs max) */
            }

            /*add a paragraph!*/
            add_paragraph_after(doc, paragraph_num);
            paragraph_num++;

        } else {
            /*If line is NOT empty...ADD IT TO THE CURRENT PARAGRAPH! :D*/
            /*Performs the function call and then checks the output*/
            /* Remove the newline character at the end of the line */
            line[strcspn(line, "\n")] = '\0'; /*WHY?: because fgets() literally reads in the new line escape sequence and we need to counter that! >:D*/
            /*strspn returns an unsigned int representing the index in which the "\n" character can
            be found in the line and then using that number, we are able to replace that literal "\n"
            with '\0' (null character)*/
            if (add_line_after(doc, paragraph_num,
                               doc->paragraphs[paragraph_num - 1].number_of_lines, line) == FAILURE) {
                fclose(file); /*close the file ;]*/
                return FAILURE;
            }
        }
    }

    fclose(file); /* close the file ;] */
    return SUCCESS;
}

/* Saves the document's content to a specified file (overwriting the file and its contents)
...lol, kind of like the "w" option when you fopen() :D*/
int save_document(Document *doc, const char *filename) {

    FILE *file;
    int i, j;

    if (doc == NULL || filename == NULL) {
        return FAILURE;
    }

    file = fopen(filename, "w"); /* Open the file to write (overwrite mode) */

    if (file == NULL) {
        return FAILURE;
    }

    /* Loop through the paragraphs */
    for (i = 0; i < doc->number_of_paragraphs; i++) {
        /* Loop through the lines within each paragraph */
        /*for ALL the lines associated with the paragraph...*/
        for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
            fprintf(file, "%s\n", doc->paragraphs[i].lines[j]); /* write each line into the file! */
        }
        fprintf(file, "\n"); /* Separate paragraphs by a newline */
    }

    fclose(file); /* Close the file ;] */

    return SUCCESS;
}