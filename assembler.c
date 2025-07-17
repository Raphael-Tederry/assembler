/**
 * Final Project – System Programming Lab (MMN14)
 * Course: 20465 – Spring 2025, Open University of Israel
 * 
 * A simple Hello World program to test the development environment.
 * This will eventually become the main assembler program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line_from_file(const char* filename, int line_number);

/**
 * Main function - entry point of the assembler program
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[])
{
    char* line = read_line_from_file("README.md", 1);
    printf("%s", line);
    
    
    return EXIT_SUCCESS;
} 

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
                strcpy_s(line, strlen(buffer) + 1, buffer);
            }
            break;
        }
    }

    fclose(file);
    return line;
}