#include <stdio.h>
#include <ctype.h>

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

int main() {
    printf("%d\n", is_string_valid("\n\n\n\t\t\t   \t"));
    printf("%d\n", is_string_valid("h"));
    return 0;
}