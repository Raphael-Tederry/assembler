#ifndef LINES_CONTAINER_H
#define LINES_CONTAINER_H

/* the different types of line containers we can use*/
typedef enum {
    AM_FILE,    /* the file with the openned macros */
    AS_FILE,    /* the origin file as we get it */
    OB_FILE,    /* final file of the project after the assembler */
    MACRO       /* macro - a pice of code */
} container_type_t;

/*array of lines each line is an array of words- can be a file or a macro*/
typedef struct lines_container{
    container_type_t type; 
    char* name;
    char*** lines;  // Changed from char** to char***
    int lines_index;
    int lines_capacity;
} LC;

/* Function declarations */
struct lines_container get_lines_container_by_name(int array_size, struct lines_container* array, char* name);
int copy_lines_between_lines_container(struct lines_container* destination, struct lines_container origin);
int resize_lines_container(struct lines_container* container);

#endif /* LINES_CONTAINER_H */ 