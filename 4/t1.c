#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max_objekt_size = 7,
    max_command_size = 4;

const short left_side = 1,
            right_side = 0;

void CheckMemAlloc(char* str){
    if(str == NULL){
        exit(1);
    }
}

short ChekCriticalSituations(char* on_side[3]){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if((strcmp(on_side[i], "goat") == 0) && (strcmp(on_side[j], "cabbage") == 0)){
                printf("Коза съела капусту\n");
                return 1;
            }
            if((strcmp(on_side[i], "wolf") == 0) && (strcmp(on_side[j], "goat") == 0)) {
                printf("Волк съел козу\n");
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char* in_boat = (char*)malloc(max_objekt_size + 1);
    CheckMemAlloc(in_boat);
    *in_boat = '\0';
    char* object = (char*)malloc(max_objekt_size + 1);
    CheckMemAlloc(object);
    *object = '\0';
    char* command = (char*)malloc(max_command_size + 1);
    CheckMemAlloc(command);
    *command = '\0';
    char* on_left[3];
    char* on_right[3];
    short position_of_boat = right_side; 
    for(int i = 0; i < 3; i++){
        on_left[i] = (char*)malloc(max_objekt_size + 1);
        CheckMemAlloc(on_left[i]);
        *on_left[i] = '\0';
        on_right[i] = (char*)malloc(max_objekt_size + 1);
        CheckMemAlloc(on_right[i]);
        *on_right[i] = '\0';
    }


    on_right[0] = "goat";
    on_right[1] = "wolf";
    on_right[2] = "cabbage";

    while(scanf("%s", command) != EOF){
        if(strcmp(command, "take") == 0){
            if(scanf("%s", object) == EOF){
                printf("Достигнут конец файла\n");
                exit(1);
            }
            in_boat = object;
            // strcpy(in_boat, object); почему-то сегфолд при втором сробатывании 
            for(int i = 0; i < 3; i++){
                if(position_of_boat == right_side){
                    if(strcmp(on_right[i], object) == 0){
                        on_right[i] = "\0";
                        break;
                    }
                } else {
                    if(strcmp(on_left[i], object) == 0){
                        on_left[i] = "\0";
                        break;
                    }
                }
            }
        }
        else if(strcmp(command, "put") == 0){
            for(int i = 0; i < 3; i++){
                if(position_of_boat == right_side){
                    if(strcmp(on_right[i], "\0") == 0){
                        strcpy(on_right[i], in_boat);
                        break;
                    }
                } else {
                    if(strcmp(on_left[i], "\0") == 0){
                        strcpy(on_left[i], in_boat);
                        break;
                    }
                }
            }
            in_boat = "\0";
        }
        else if(strcmp(command, "move") == 0){
            if(position_of_boat == right_side){
                position_of_boat = left_side;
                ChekCriticalSituations(on_right);
            } else {
                position_of_boat = right_side;
                ChekCriticalSituations(on_left);
                
            }
        }
    }

    free(in_boat);
    free(object);
    free(command);
    for(int i = 0; i < 3; i++){
        free(on_left[i]); 
        free(on_right[i]);
    }
    return 0;
}
