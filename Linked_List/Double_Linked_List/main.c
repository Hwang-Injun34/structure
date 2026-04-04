#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef enum _MY_MENU{
    MENU_EXIT = 0,
    MENU_ADD_NODE,
    MENU_REMOVE_FRONT,
    MENU_REMOVE_REAR,
    MENU_REMOVE_BY_VALUE,
    MENU_CLEAR_LIST,
    MENU_PRINT_NODE, 
    MENU_PRINT_ALL,
    MENU_PRINT_REVERSE,
    MENU_INVALID 
} MY_MENU;

void Pause(void){
    printf("계속 하려면 Enter...");
    while(getchar() != '\n');
}

void ClearBuffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

MY_MENU PrintMenu(void){
    int temp = 0;

    system("clear");
    printf(
        "\n========== MENU ==========\n"
        "[1] Add Node        [2] Remove Front\n"
        "[3] Remove Rear     [4] Remove By Value\n"
        "[5] Clear List      [6] Print Node\n"
        "[7] Print All       [8] Print Reverse\n"
        "[0] Exit\n"
        "==========================\n"
    );

    if(scanf("%d", &temp) != 1){
        ClearBuffer();
        printf("입력 오류\n");
        return MENU_INVALID;
    }

    ClearBuffer();

    if(temp < 0 || temp > 8){
        printf("범위가 벗어났습니다.\n");
        return MENU_INVALID;
    }

    return (MY_MENU)temp;
}


int main(int argc, char *argv[]){
    MY_MENU menu; 
    LIST list;
    InitList(&list);
    
    while((menu=PrintMenu()) != MENU_EXIT){
        switch(menu){
            case MENU_ADD_NODE:
                // 완료
                // AddNode(&list, 1);
                DummyData(&list);
                break;
            case MENU_REMOVE_FRONT:
                // 완료
                RemoveFront(&list);
                break;
            case MENU_REMOVE_REAR:
                // 완료
                RemoveRear(&list);
                break;
            case MENU_REMOVE_BY_VALUE:
                // 완료
                RemoveByValue(&list, 1);
                break;
            case MENU_CLEAR_LIST:
                // 완료
                ClearList(&list);
                break;
            case MENU_PRINT_NODE:
                PrintNode(&list, 1);
                break;
            case MENU_PRINT_ALL:
                // 완료
                PrintAll(&list);
                break;
            case MENU_PRINT_REVERSE:
                PrintReverse(&list);
                break; 
            case MENU_INVALID:
                break;
            default:
                break;
        
        }
        Pause();
    }

    Terminate(&list);
    return 0;
}