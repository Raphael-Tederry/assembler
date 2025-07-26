/* crud.c in charge of creating reading updating and deleting files */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "string_handler.c"





/* get_files(file): ruben working
 *     will get the cmd input
 *     check if the names corespond to files(.as) in the directory
 *     read the files into list(all the files) of list(all the lines) of list(all the the words)
 *         first line in file is the name of the file
 *     ERROR handling dont stop the project
 *     return the phrases extracted 
 */
char **** get_files(int number_of_files, char* files_name[]) {
    int i;
   char ***files = (char***)malloc(sizeof(*files) *number_of_files);
   if (files == NULL){
    //handle erorrs
    return NULL;
   }
   for (i = 0; i < number_of_files; i++){
    files[i] = get_file(files_name[i]);
   }
    return files;
}
 char*** get_file(char* file__base_name){
    char** output_file;
    char* file_as_name = add_ending_to_name(file__base_name, ".as");
    FILE* input_file = fopen(file_as_name, "r");
    if (input_file == NULL){
        //error handling
    }
    else {
        
    }
    free(file_as_name);
    fclose(input_file);
    return output_file;
}

char* read_line_fro_file()


/* save_file(file_name, ending, lines, lines_index): 
 *     save a file(list of lines of list of words) by name and ending(am/ob)
 */


