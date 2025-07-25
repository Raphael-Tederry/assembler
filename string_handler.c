/* string_handler.c in charge of handling and manipulating strings */
#include <stdio.h>

/*is_string_valid: check if string isnt empty or only white spaces
@param str: the string to check
return 1 if the string contains at least 1 non-whitespace character, otherwise 0*/

int is_string_valid(const char* str) {
    if (str == NULL){
        return 0;
    }

    while (*str != '\0') {
        if (!isspace((unsigned char)*str)) {
            return 1;
        }
        str++;
    }
    return 0;
}

char* add_ending_to_name(char *file_base_name, char *ending){
    char *file_as_name = malloc(strlen(file_base_name) + strlen(ending) + 1);
    if(file_as_name == NULL){
        // failed to allocate memory for full name
        return NULL;
    }if (is_string_valid(file_base_name) && is_string_valid(ending)){
        sprintf(file_as_name, "%s%s", file_base_name, ending);
        return file_as_name;
    } else return NULL;
} 


/**need to be done
 * 
 * 
 * 
 * 
 * 
 * 
 */

int is_lable(char* word){
    /*     get a string
     *     return true if it can be a lable
     */
        return 1;
    }


/* check_macro_end(line):
 *     get the line containig macro_end and check its leagal
 *     if yes return 0 otherwise return an apropriait error
 */



