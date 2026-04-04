#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef enum _MY_MENU{
    MENU_EXIT = 0,
    MENU_ENQUEUE,
    MENU_DEQUEUE,
    MENU_ISEMPTY,
    MENU_PRINT_ALL,
    MENU_INVALID
} MY_MENU;


void Pause(void){
    printf("계속 하려면 Enter...");
    while(getchar() != '\n');
}

void ClearBuffer(void){
    int c = 0;
    while((c=getchar()) != '\n' && c != EOF) ;
}

MY_MENU PrintMenu(void){
    int temp = 0;

    system("clear");
    printf(
    "\n=============== Menu ================\n"
    "[1] Enqueue            [2] Dequeue\n"
    "[3] IsEmpty            [4] Print All\n"
    "[0] Exit\n"
    "\n=============== Menu ================\n"
    );

    if(scanf("%d", &temp) != 1){
        ClearBuffer();
        printf("입력 오류\n");
        return MENU_INVALID;
    }

    ClearBuffer();

    if(temp < 0 || temp > 4){
        printf("범위를 벗어남\n");
        return MENU_INVALID;
    }
    return (MY_MENU)temp;
}


int main(int argc, char *argv[]){
    MY_MENU menu = 0;
    int data = 0;

    QUEUE q;
    Init(&q, 5);

    while((menu=PrintMenu()) != MENU_EXIT){
        switch(menu){
            case MENU_ENQUEUE:
                //Enqueue(&q, 1);
                DummyData(&q);
                break;
            case MENU_DEQUEUE:
                Dequeue(&q, &data);
                printf("%d", data);
                break;
            case MENU_ISEMPTY:
                if(IsEmpty(&q)){
                    printf("비어있습니다.\n");
                }
                printf("데이터가 있습니다.\n");
                break;
            case MENU_PRINT_ALL:
                PrintAll(&q);
                break;
            case MENU_INVALID:
                break;
            default:
                break;
        }
        Pause();
    }
    Terminate(&q);
    return 0;
}