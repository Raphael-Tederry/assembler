/**
 * Final Project – System Programming Lab (MMN14)
 * Course: 20465 – Spring 2025, Open University of Israel
 * 
 * A simple Hello World program to test the development environment.
 * This will eventually become the main assembler program.
 */

#include <stdio.h>
#include <stdlib.h>
#include "crud.c"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/**
 * Main function - entry point of the assembler program
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings should be the files to assemble
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[])
{
    char* line;
    
    line = read_line_from_file("README.md", 1);
    printf("%s", line);
    
    
    return EXIT_SUCCESS;
} 

