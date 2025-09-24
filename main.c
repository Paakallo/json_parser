#include <stdio.h>
#include <stdlib.h>

// FUNCTIONALITY:
// l - load and check json
// s - show json records
// v [record_name] - show record value
// e [record_name] - edit json record
// d [record_name] - delete json record
// i [record_name] - insert json record
// r - return to menu
// q - quit

typedef enum usr_in_{LOAD, SHOW, VALUE, EDIT, DELETE, INSERT, RETURN, QUIT} UserInput;

int main(){
    UserInput in_char;
    char input;
    while (1){
        input = getchar();
        switch (input){
            case 'l':
                in_char = LOAD;
                break;
            case 's':
                in_char = SHOW;
                break;
            case 'v':
                in_char = VALUE;
                break;
            case 'e':
                in_char = EDIT;
                break;
            case 'd':
                in_char = DELETE;
                break;
            case 'i':
                in_char = INSERT;
                break;
            case 'r':
                in_char = RETURN;
                break;
            case 'q':
                in_char = QUIT;
                exit(1);
                break;
            default:
                break;
        }
    }
}