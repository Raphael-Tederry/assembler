#include <stdlib.h> /* Required for malloc*/
#include <string.h>
#include "lines_container.h"
#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/* Definition of the NULL lines_container constant */
struct lines_container NULL_LC = {
    NULL_FILE,  /* type */
    NULL,       /* name */
    NULL,       /* lines */
    0,          /* lines_index */
    0           /* lines_capacity */
};



/**raph done!
 * will add a line to the lines_container
 *
 * process:
 * we resize the lines_container if needed
 * we add the line to the lines_container
 *
 * @param container the pointer to the lines_container to add the line to
 * @param line the line to add to the lines_container
 * @return EXIT_SUCCESS if the line was added, EXIT_FAILURE otherwise
 */
int add_line_to_lines_container(struct lines_container* container, char** line){
    if(resize_lines_container(container) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    container->lines[container->lines_index] = line;
    container->lines_index++;
    return EXIT_SUCCESS;
}




/**raph done!
 * will copy all the lines from the origin lines_container to the destination lines_container
 * this function will add them to the destination lines_container no overwriting
 * TODO:if the destination lines_container is not big enough it will resize it
 *
 * process:
 * we go over the origin lines and add them to the destination lines
 * we are called when everything is correct and there are no checks to do
 *
 * @param destination the pointer to the destination lines_container to add the lines to
 * @param origin the origin lines_container to copy the lines from
 * @return EXIT_SUCCESS
 */
 int copy_lines_between_lines_container(struct lines_container* destination, struct lines_container origin){
    int i;
    for(i = 0; i < origin.lines_index; i++){
        if(resize_lines_container(destination) == EXIT_FAILURE){
            return EXIT_FAILURE;
        }
        destination->lines[destination->lines_index] = origin.lines[i];
        destination->lines_index++;
    }
    return EXIT_SUCCESS;
}

/**raph done!
 * will resize the lines_container if needed
 *
 * process:
 * we check if the lines_capacity is 0 or the lines array is NULL (first time we call the function)
 *      we initialize the lines_capacity to 2 and realloc the lines array to a size of 2
 *
 * we check if the lines_index is equal to the lines_capacity
 *      we double the lines_capacity
 *      we realloc the lines array to the new size
 *
 * if we failed to allocate memory we return EXIT_FAILURE
 *
 * @param container the pointer to the lines_container to resize
 * @return EXIT_SUCCESS if the lines_container was resized, EXIT_FAILURE otherwise
 */
int resize_lines_container(struct lines_container* container){
    if(container->lines_capacity == 0 || container->lines == NULL){
        container->lines_capacity = 2;
        container->lines = malloc(container->lines_capacity * sizeof(char**));
        if(container->lines == NULL){
            return EXIT_FAILURE;
        }
    }
    if(container->lines_index == container->lines_capacity){
        container->lines_capacity *= 2;
        container->lines = realloc(container->lines,container->lines_capacity * sizeof(char**));
        if(container->lines == NULL){
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/**raph done!
 * will return the lines_container of from an array of lines_container with the given name
 *
 * process:
 * we go over the array and check if the name is in the array
 * if we find it we return the lines_container of the macro
 * if we don't find it we return NULL
 *
 * 
 * @param array_size size of the array
 * @param array array of lines_container
 * @param name string to comper to the array names
 * @return EXIT_SUCCESS if the name is in the array, EXIT_FAILURE otherwise
 */
 struct lines_container get_lines_container_by_name(int array_size, struct lines_container* array, char* name){
    int i;
    for(i = 0; i < array_size; i++){
        if(strcmp(array[i].name, name)==0){
            return array[i];
        }
    }
    return NULL_LC;
}





