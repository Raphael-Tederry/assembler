/* pre_assembly.c in charge of pre-assembly(openning the macros in a new file) of the files mostly following the algorithm given in the task file */


// #include "crud.c"
// #include <corecrt_search.h>
#include <stdio.h>
#include <stdlib.h> // Required for malloc
#include <string.h>
#include "lines_container.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define END_OF_FILE NULL
#define END_OF_LINE NULL


/*in another file*/
char*** get_file(char* file_name);
int is_valid_macro(char* word);

/* in the file*/
struct lines_container* resize_macro_list_if_needed(struct lines_container*, int*, int);
struct lines_container pre_assembly_file(struct lines_container);
int macro_initialization_handler(int , struct lines_container* , char** , int , struct lines_container* , char* );
int macro_end_handler(char** , int* , struct lines_container* , char* , int* , struct lines_container* );

/*need to be created in an another file?*/
int is_instruction(char* word);
int is_suggestion(char* word);
void save_file(char* file_name, char* ending, char*** lines, int lines_index);


/**raph woking
    * main function of pre_assembly returns lines_container* of the am files if successfull if we had an error we will return NULL
    * process:
    * get the files name given to main from the command line, and thier number
    * if there are no files to assemble, the program will end successfully
    * run the pre_assembly_file function on the files one by one (in ordar to save memory we don't need to save all the files in memory at once),
    *   create a lines_container and send the it to the pre_assembly_file function
    * return the new am files
    * 
    *
    * @paramargc number of files given to main
    * @param argv array of files names given to main
    * @return array of files(am) containing array of lines containing array of words
*/
struct lines_container* pre_assembly(int argc, char *argv[]){
    struct lines_container* am_files = malloc(argc * sizeof(struct lines_container));
    struct lines_container new_am_file;
    if (!am_files) {
        return NULL;  // Handle allocation failure
    }
    
    int i;
    struct lines_container old_as_file;
    for(i = 0; i < argc; i++){
        old_as_file.type = AS_FILE;
        old_as_file.name = argv[i];
        old_as_file.lines = get_file(argv[i]); // TODO: check if this is correct get_file returns char**
        printf("riminder to do error handling to files");
        new_am_file = pre_assembly_file(old_as_file);
        if (new_am_file.name) {
            am_files[i] = new_am_file;
        }
        else {
            return NULL;
        }
    }
    return am_files;
}
/**raph woking
    * will go over a file in lines_container format and returns a new lines_container with the
    * macros openned
    * process:
    * basic initialization of variables
    * going over the lines of the given file
    *   we check the firs word(field) of the line
    *   if its a macro we !!!!!add it to the macro list
    *   if its a macro_end !!!!we add the macro to the file
    *   if its a lable we !!!add it to the file
    *   if its a word we !!!!add it to the file
    * 
    * 
    * 
    * @param as_file a lines_container of the 'as' file to pre-assemble
    * @return a lines_container of the new 'am' file with the macros openned
 */
struct lines_container pre_assembly_file(struct lines_container as_file){ //TODO: idea: when printing errors we should print the line number and the line itself
    int in_macro = 0;
    int macro_list_capacity = 2;
    int macro_list_index = 0;
    int word_index = 0;
    int line_index_as_file;
    char* first_field;

    /*lines_container{container_type_t type; char* name; char*** lines; int lines_index; int lines_capacity;}*/
    struct lines_container temp;
    struct lines_container am_file = {AM_FILE,as_file.name, NULL, 0, as_file.lines_capacity}; /*we assume the am file will be at least the same size as the as file*/
    struct lines_container current_macro = {MACRO, NULL, NULL, 0, 2};
    struct lines_container* macro_list = malloc(2 * sizeof(struct lines_container)); // Start small

    /*going over the lines of the file aka main pre assembly*/
    for(line_index_as_file=0; as_file.lines[line_index_as_file] != END_OF_FILE; line_index_as_file++){
        macro_list = resize_macro_list_if_needed(macro_list, &macro_list_capacity, macro_list_index);
        if (!macro_list) {/*if we failed to allocate memory for the macro list, we return NULL*/
            printf("while processing the file %s, failed to allocate memory for the macro list", as_file.name);// TODO: ERROR HANDLING
            return (struct lines_container){NULL, NULL}; 
        }

        first_field = as_file.lines[line_index_as_file][0];
        if(strcmp(first_field, "macro")==0){
            /*if the macro initialization is correct we set in_macro to 1, if not correct, we return NULL the error is handled in the macro_initialization_handler*/
            if(!(in_macro = macro_initialization_handler(macro_list_index, macro_list, as_file.lines[line_index_as_file], in_macro, &current_macro, as_file.name))){
                return (struct lines_container){NULL, NULL};
            }
        } else if(strcmp(first_field, "macro_end")==0){
            if(!macro_end_handler(as_file.lines[line_index_as_file], &in_macro, &current_macro, as_file.name, &macro_list_index, macro_list)){
                return (struct lines_container){NULL, NULL};
            }
        } else if(in_macro){
            current_macro.lines[current_macro.lines_index] = as_file.lines[line_index_as_file];
            current_macro.lines_index++;
        } else if((temp = get_lines_container_by_name(macro_list_index, macro_list, first_field)).name){
            /*we know the name is in the macro list, we need to add the macro to the am file*/
            if(!copy_lines_between_lines_container(&am_file, temp)){
                printf("while processing the file %s, failed to copy the lines of the macro to the am file", am_file.name);// TODO: ERROR HANDLING
                return (struct lines_container){NULL, NULL};
            }
        }else { /*adding to the am file*/
            am_file.lines[am_file.lines_index] = as_file.lines[line_index_as_file];
            am_file.lines_index++;
        }
    }
    am_file.lines[am_file.lines_index] = END_OF_FILE;
    save_file(am_file.name, "am", am_file.lines, am_file.lines_index);

    return am_file;
}


/**raph done!
 * will check if the macro initialization is correct and if not we return an error
 * if it is correct we set the macro name to the second word
 *
 * process:
 * we check if we are in a macro
 * we check if the line has only one word
 * we check if the line has only two words (macro and its name)
    * we check if the name is not an already set previous macro
    * we check if the name is not an instruction or suggestion
    * we check if the name is a valid macro name
 * if we fail in any of the checks we return an error
 * if we succeed we set the macro name to the second word
 *
 * @param macro_list_index index of the macro list length
 * @param macro_list list of macros
 * @param line array of words to check
 * @param in_macro 1 if we are in a macro, 0 otherwise
 * @param macro the macro to update
 * @param name name of the 'as' file
 * @return EXIT_SUCCESS if the initialization is correct, EXIT_FAILURE otherwise
 */
int macro_initialization_handler(int macro_list_index, struct lines_container* macro_list, char** line, int in_macro, struct lines_container* macro, char* name){
    if(in_macro){
        printf("while processing the file %s, found a macro imbeded in a macro, shouldent be possible according to the task file", name);// TODO: ERROR HANDLING
        return EXIT_FAILURE;
    } if(line[1] == NULL){ /*no name*/
        printf("while processing the file %s, found a macro with no name, wich is an invalid macro initialization", name);// TODO: ERROR HANDLING
        return EXIT_FAILURE;
    } if(line[1] != NULL && line[2] == NULL){ // we know line[0] is macro and line[1] is its name, only 2 words allowed, TODO: better check then this
        if(get_lines_container_by_name(macro_list_index, macro_list, line[1]).name){
            printf("while processing the file %s, found a macro with the same name as a previous macro", name);// TODO: ERROR HANDLING
            return EXIT_FAILURE;
        } if(is_instruction(line[1]) || is_suggestion(line[1]) ){
            printf("while processing the file %s, found a macro with a name that is an instruction or suggestion", name);// TODO: ERROR HANDLING
            return EXIT_FAILURE;
        } if(is_valid_macro(line[1])){
        /*only two fields and the name is valid?*/
        macro->name = line[1];  // modifies the original(pointers sign)
        return EXIT_SUCCESS;
        }
    }
    printf("while processing the file %s, found a macro with more then two fields", name);// TODO: ERROR HANDLING
    return EXIT_FAILURE;
}


/**raph done!
 * will check if the macro end is correct and if not we return an error
 * if it is correct we add the macro to the macro list
 * we restart in_macro and macro for the next macro
 *
 * process:
 * we check if we are not in a macro
 * 
 * we check if the line has only one field more then that is an error
 * we add the macro to the macro list
 * we restart in_macro and macro for the next macro
 *
 * @param line array of words to check(first one contains macro_end)
 * @param in_macro 1 if we are in a macro, 0 otherwise
 * @param macro the macro to update
 * @param name name of the 'as' file
 * @param macro_list_index index of the macro list to add the macro to
 * @param macro_list list of macros
 * @return EXIT_SUCCESS if the end is correct, EXIT_FAILURE otherwise
 */
int macro_end_handler(char** line, int* in_macro, struct lines_container* macro, char* name, int* macro_list_index, struct lines_container* macro_list){
    if(!*in_macro){
        printf("while processing the file %s, found a macro_end without a macro.", name);// TODO: ERROR HANDLING
        return EXIT_FAILURE;
    } if(line[1] != END_OF_LINE){ //TODO: better check then this, we should only have one field
        printf("while processing the file %s, found a macro_end with more then one field.", name);// TODO: ERROR HANDLING
        return EXIT_FAILURE;
    }/*this is a legal macro_end*/
    macro_list[*macro_list_index] = *macro;
    (*macro_list_index)++;
    *in_macro = 0;
    *macro = (struct lines_container){NULL, NULL};
    return EXIT_SUCCESS;
}


/**raph done!
 * resizes macro list if needed by doubling capacity
 * (doubling the size is more efficient than adding by constant 2 -> 4 -> 8 ... ->1024 comperd to 2 -> 4 -> 6 ... -> 20)
 *
 * @param macro_list current macro list
 * @param macro_list_capacity pointer to current capacity (will be updated)
 * @param macro_list_index current number of macros
 * @return new macro_list pointer, or NULL on allocation failure
 */
 struct lines_container* resize_macro_list_if_needed(struct lines_container* macro_list, int* macro_list_capacity, int macro_list_index){
    if (macro_list_index >= *macro_list_capacity) {
        *macro_list_capacity *= 2; // Double the size
        macro_list = realloc(macro_list, (*macro_list_capacity) * sizeof(struct lines_container));
        if (!macro_list) {
            return NULL; // Allocation failure
        }
    }
    return macro_list;
}



