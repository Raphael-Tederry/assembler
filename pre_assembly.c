/* pre_assembly.c in charge of pre-assembly(openning the macros in a new file) of the files mostly following the algorithm given in the task file */


// #include "crud.c"
#include <stdio.h>
#include <stdlib.h> // Required for malloc
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define END_OF_FILE NULL
#define END_OF_LINE NULL


/*array of lines each line is an array of words- can be a file or a macro*/
typedef struct lines_container{
    int type; // macro as/am/ob file 
    char* name;
    char*** lines;  // Changed from char** to char***
    int lines_index;
    int lines_capacity;
} lines_container;

/*in another file*/
char*** get_file(char* file_name);
int is_valid_macro(char* word);

/* in the file*/
lines_container* resize_macro_list_if_needed(lines_container*, int*, int);
lines_container pre_assembly_file(lines_container);
lines_container check_name_in_lines_container_array(int , lines_container* , char* );
int macro_initialization_handler(int , lines_container* , char** , int , lines_container* , char* );
int macro_end_handler(char** , int* , lines_container* , char* , int* , lines_container* );
int copy_lines_container_lines_to_lines_container(lines_container*, lines_container);

/*need to be created in an another file?*/
int is_instruction(char* word);
int is_suggestion(char* word);
void save_file(char* file_name, char ending, char*** lines, int lines_index);


/**raph woking
    * main function of pre_assembly  lines_container* of the am files if successfull if we had an error we will return NULL
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
lines_container* pre_assembly(int argc, char *argv[]){
    lines_container* am_files = malloc(argc * sizeof(lines_container));
    lines_container new_am_file;
    if (!am_files) {
        return am_files;  // Handle allocation failure
    }
    
    int i;
    lines_container old_as_file;
    for(i = 0; i < argc; i++){
        old_as_file.name = argv[i];
        old_as_file.lines = get_file(argv[i]); // TODO: check if this is correct get_file returns char**
        printf("riminder do so error handling to files");
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
lines_container pre_assembly_file(lines_container as_file){ //TODO: idea: when printing errors we should print the line number and the line itself
    int in_macro = 0;
    int macro_list_capacity = 2;
    int macro_list_index = 0;
    int word_index = 0;
    int line_index_as_file;
    char* first_field;

    lines_container temp;
    lines_container am_file = {0 ,as_file.name, NULL, NULL};
    lines_container current_macro = {NULL, NULL};
    lines_container* macro_list = malloc(2 * sizeof(lines_container)); // Start small

    /*going over the lines of the file aka main pre assembly*/
    for(line_index_as_file=0; as_file.lines[line_index_as_file] != END_OF_FILE; line_index_as_file++){
        macro_list = resize_macro_list_if_needed(macro_list, &macro_list_capacity, macro_list_index);
        if (!macro_list) {/*if we failed to allocate memory for the macro list, we return NULL*/
            printf("while processing the file %s, failed to allocate memory for the macro list", as_file.name);// TODO: ERROR HANDLING
            return (lines_container){NULL, NULL}; 
        }

        first_field = as_file.lines[line_index_as_file][0];
        if(strcmp(first_field, "macro")==0){
            /*if the macro initialization is correct we set in_macro to 1, if not correct, we return NULL the error is handled in the macro_initialization_handler*/
            if(!(in_macro = macro_initialization_handler(macro_list_index, macro_list, as_file.lines[line_index_as_file], in_macro, &current_macro, as_file.name))){
                return (lines_container){NULL, NULL};
            }
        } else if(strcmp(first_field, "macro_end")==0){
            if(!macro_end_handler(as_file.lines[line_index_as_file], &in_macro, &current_macro, as_file.name, &macro_list_index, macro_list)){
                return (lines_container){NULL, NULL};
            }
        } else if(in_macro){
            current_macro.lines[current_macro.lines_index] = as_file.lines[line_index_as_file];
            current_macro.lines_index++;
        } else if((temp = check_name_in_lines_container_array(macro_list_index, macro_list, first_field)).name){
            /*we know the name is in the macro list, we need to add the macro to the am file*/
            if(!copy_lines_container_lines_to_lines_container(&am_file, temp)){
                printf("while processing the file %s, failed to copy the lines of the macro to the am file", am_file.name);// TODO: ERROR HANDLING
                return (lines_container){NULL, NULL};
            }
        }else { /*adding to the am file*/
            am_file.lines[am_file.lines_index] = as_file.lines[line_index_as_file];
            am_file.lines_index++;
        }
    }
    am_file.lines[am_file.lines_index] = END_OF_FILE;
    save_file(am_file.name, 'am', am_file.lines, am_file.lines_index);

    return am_file;
}





/**raph done!
 *
 * process:
 * we go over the origin lines and add them to the destination lines
 * we are called when everything is correct and there are no checks to do
 *
 * @param destination the pointer to the destination lines_container to add the lines to
 * @param origin the origin lines_container to copy the lines from
 * @return EXIT_SUCCESS
 */
int copy_lines_container_lines_to_lines_container(lines_container* destination, lines_container origin){
    int i;
    for(i = 0; i < origin.lines_index; i++){
        destination->lines[destination->lines_index] = origin.lines[i];
        destination->lines_index++;
    }
    return EXIT_SUCCESS;
}



/**raph done!
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
lines_container check_name_in_lines_container_array(int array_size, lines_container* array, char* name){
    int i;
    for(i = 0; i < array_size; i++){
        if(strcmp(array[i].name, name)==0){
            return array[i];
        }
    }
    return (lines_container){NULL, NULL};
}

/**raph done!
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
int macro_initialization_handler(int macro_list_index, lines_container* macro_list, char** line, int in_macro, lines_container* macro, char* name){
    if(in_macro){
        printf("while processing the file %s, found a macro imbeded in a macro, shouldent be possible according to the task file", name);// TODO: ERROR HANDLING
        return EXIT_FAILURE;
    } if(line[1] == NULL){ /*no name*/
        printf("while processing the file %s, found a macro with no name, wich is an invalid macro initialization", name);// TODO: ERROR HANDLING
        return EXIT_FAILURE;
    } if(line[1] != NULL && line[2] == NULL){ // we know line[0] is macro and line[1] is its name, only 2 words allowed, TODO: better check then this
        if(check_name_in_lines_container_array(macro_list_index, macro_list, line[1]).name){
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
int macro_end_handler(char** line, int* in_macro, lines_container* macro, char* name, int* macro_list_index, lines_container* macro_list){
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
    *macro = (lines_container){NULL, NULL};
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
 lines_container* resize_macro_list_if_needed(lines_container* macro_list, int* macro_list_capacity, int macro_list_index) {
    if (macro_list_index >= *macro_list_capacity) {
        *macro_list_capacity *= 2; // Double the size
        macro_list = realloc(macro_list, (*macro_list_capacity) * sizeof(lines_container));
        if (!macro_list) {
            return NULL; // Allocation failure
        }
    }
    return macro_list;
}




/*
pre_assembly_file(char** file):
    in_macro = false
    struct list_of_macro = null
    macro_head = null 
    new_file = "" \\ list of list

    for (line in file):
        first_filed = line[0]
        if (first_filed == "macro")
            if(!errors = handel_macro_start(line, list_of_macro, *macro_head))
                if (in_macro == true):
                    print_error(error: was promised to not have two macros imbeded)
                in_macro = true
            else:
                print_error(errors)
        else if (first_filed == "macro_end")
            if(errors = check_macro_end(line))
                print_error(errors_list)
                break
            in_macro = false
            macro_head = null
        else if (in_macro == true)
            add_line_to_macro(macro_head,line)
        else if (is_lable(first_filed) and line[1]== "macro"):
            print_error(ERROR cant be lable at start of macro)
        else if (first_filed in list_of_macro):
            copy_macro_to_file(new_file, first_filed)   \\its not a file yet its a list of list
        else 
            add_line_to_file(new_file,line) \\its not a file yet its a list of list
        location++

    save_file(new_file, file_name, ending)
    return new_file

*/