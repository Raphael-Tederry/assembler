// crud.c in charge of creating reading updating and deleting files


#include <string.h>
#include <stdio.h>
#include <stdlib.h>







char* read_line_from_file(const char* filename, int line_number)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    char buffer[1024];
    char* line = NULL;
    int current_line = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        current_line++;
        if (current_line == line_number) {
            line = malloc(strlen(buffer) + 1);
            if (line != NULL) {
                strcpy(line, buffer);
            }
            break;
        }
    }

    fclose(file);
    return line;
}