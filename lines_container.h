#ifndef LINES_CONTAINER_H
#define LINES_CONTAINER_H

/*array of lines each line is an array of words- can be a file or a macro*/
typedef struct lines_container{
    int type; // macro as/am/ob file 
    char* name;
    char*** lines;  // Changed from char** to char***
    int lines_index;
    int lines_capacity;
} LC;

/* Function declarations */
struct lines_container get_lines_container_by_name(int array_size, struct lines_container* array, char* name);
int copy_lines_between_lines_container(struct lines_container* destination, struct lines_container origin);

#endif /* LINES_CONTAINER_H */ 