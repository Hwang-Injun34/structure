#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

typedef enum _MY_MENU{
    MENU_EXIT = 0,
    MENU_INSERT, 
    MENU_DELETE,
    MENU_SEARCH,
    MENU_PRINT_TABLE,
    MENU_CLEAR_TABLE,
    MENU_INVALID
} MY_MENU;

void Pause(void){
    printf("계속 하려면 Enter...");
    while(getchar() != '\n');
}

void ClearBuffer(void){
    int c =0;
    while((c = getchar()) != '\n' && c != EOF);
}

MY_MENU PrintMenu(void){
    int temp = 0;
    
    system("clear");
    printf(
        "\n=========== MENU ===========\n"
        "[1] Insert         [2] Delete\n"
        "[3] Search         [4] Print Table\n"
        "[5] Clear Table    [0] Exit\n"
        "\n============================\n"
    );


    if(scanf("%d", &temp) != 1){
        ClearBuffer();
        printf("입력 오류\n");
        return MENU_INVALID;
    }

    ClearBuffer();

    if(temp < 0 || temp > 5){
        printf("범위가 벗어났습니다.\n");
        return MENU_INVALID;
    }

    return (MY_MENU)temp;
}

int main(int argc, char *argv[]){
    MY_MENU menu; 

    HASHTABLE ht;
    InitTable(&ht);

    while((menu = PrintMenu()) != MENU_EXIT){
        switch(menu){
            case MENU_INSERT:
                // Insert(&ht);
                DummyData(&ht);
                break;
            case MENU_DELETE:
                Delete(&ht, 11);
                break;
            case MENU_SEARCH:
                Search(&ht, 12);
                break;
            case MENU_PRINT_TABLE:
                PrintTable(&ht);
                break;
            case MENU_CLEAR_TABLE:
                ClearTable(&ht);
                break;
            case MENU_INVALID:
                break;
            default:
                break;
        }
        Pause();
    }
    ClearTable(&ht);
    return 0;
}