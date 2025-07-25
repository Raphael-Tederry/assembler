/* pre_assembly.c in charge of pre-assembly(openning the macros in a new file) of the files mostly following the algorithm given in the task file */


// #include "crud.c"
#include <stdio.h>

/*array of lines each line is an array of words- can be a file or a macro*/
typedef struct lines_container{
    char* name;
    char** lines;
} lines_container;





char** pre_assembly_file(char** file);
char*** get_files(int argc, char *argv[]);




/**raph woking
    main function of pre_assembly
    get the files name given to main from the command line
    run the pre_assembly_file function on the files one by one
    return the new am files
    * @param argc number of files given to main
    * @param argv array of files names given to main
    * @return array of files(am) containing array of lines containing array of words
*/
char*** pre_assembly(int argc, char *argv[]){
    lines_container am_files[argc];
    int i;
    lines_container files[argc];
    files = get_files(argc, argv);
    printf("riminder do so error handling to files");
    for(i=0; i<sizeof(files); i++){
        am_files[i] = pre_assembly_file(files[i]);
    }
    return am_files;
}
/**
    raph woking
    * @param file array of lines containing array of words
    * @return array of lines containing array of words(the new file with the macros openned)
 */
char** pre_assembly_file(char** file){
    int in_macro = 0;
    lines_container current_macro;
    lines_container macro_list[10];
    int macro_list_index = 0;
    lines_container new_file;
    int line_index = 0;
    int word_index = 0;
    for(line_index=0; line_index<sizeof(file); line_index++){
        ;
        }
    
    return new_file;


    
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