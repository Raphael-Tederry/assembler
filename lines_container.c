#include <stdlib.h> // Required for malloc
#include <string.h>
#include "lines_container.h"


#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


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
        destination->lines[destination->lines_index] = origin.lines[i];
        destination->lines_index++;
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
    return (struct lines_container){NULL, NULL};
}





