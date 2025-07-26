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
#include "pre_assembly.c"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/**
 * Main function - entry point of the assembler program
 * 
 * if there are no files to assemble, the program will end successfully
 * otherwise, we start the pre_assembly process
 * 
 * if we dont get the am files, that means we had a failure in the pre_assembly process, the program will end with failure
 * 
 * if we get the am files, we start TODO:
 * 
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings should be the files to assemble
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[])
{
    lines_container* am_files;

    if(argc == 0){
        printf("No files to assemble");
        return EXIT_SUCCESS;
    }
    
    am_files = pre_assembly(argc, argv);
    if (!am_files) {
        return EXIT_FAILURE;  // Handle allocation failure
    }
    
    
    
    return EXIT_SUCCESS;
} 

