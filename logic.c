#include <stdio.h>
#include <stdlib.h>


typedef struct 
{       
    int arr_len;
    char name[];
    
}js_unit;


void load(){
    // TODO: handle filenames
    char filename = "test.json";
    
    bool_t parsed = 0;  
    char f_size = 0;
    FILE* file;

    file = fopen(filename, 'rb');

    if (file == NULL){
        exit(-1);
    }

    // parsing and loading

    fclose(file);
    
}

int parse(FILE *file, int offset){
    bool_t check = 0;
    fseek(file, offset, SEEK_SET);    
    
    // check if it is a list
    if (getc(file) == '['){
        fseek(file, offset, SEEK_END);    
        if (getc(file) == ']'){
            check = 1;
        } else{
            printf("Error: no closing bracket");
        }
    } else{
        printf("Error: no opening bracket");
    }


    fseek(file, offset, SEEK_SET);    
    char curr_c;

    bool_t dic = 0;
    bool_t obj_name = 0;
    bool_t obj_value = 0;
    while (!check){
        curr_c = getc(file);
        // TODO: make a check function for special characters
        if (curr_c == '{'){
            dic = 1;
        } else{
            printf("Error, no dictionary");
        }

        
        file++;
    }

    
}