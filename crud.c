/* crud.c in charge of creating reading updating and deleting files */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>







char* read_line_from_file(const char* filename, int line_number)
{
    FILE* file;
    char buffer[1024];
    char* line = NULL;
    int current_line = 0;
    
    file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

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


/* get_files(file): ruben working
 *     will get the cmd input
 *     check if the names corespond to files(.as) in the directory
 *     read the files into list(all the files) of list(all the lines) of list(all the the words)
 *         first line in file is the name of the file
 *     ERROR handling dont stop the project
 *     return the phrases extracted 
 */
char *** get_files(int number_of_files, char* files_name[]) {

   char ***files = (char***)malloc(sizeof(*files) *number_of_files);
   if (files == NULL){
    //handle erorrs
    return NULL;
   }
   for (i = 0; i <= number_of_files){
    files[i] = get_file(files[i], files_name[i]);
   }
    return files;
}
 get_file(char** file, char* file_name){
    FILE *file = fopen(file_name);

    call a function to fill words in line
}
get_line


/* save_file(file, file_name, ending): 
 *     save a file(list of lines of list of words) by name and ending(am/ob)
 */


