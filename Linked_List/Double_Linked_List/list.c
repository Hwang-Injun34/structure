#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


// 초기화
void InitList(LIST *list){
    list->head = (NODE *)malloc(sizeof(NODE));
    list->tail = (NODE *)malloc(sizeof(NODE));

    list->head->next = list->tail;
    list->head->prev = NULL;

    list->tail->prev = list->head;
    list->tail->next = NULL;
}

// 삽입 맨 뒤
void AddNode(LIST *list, int data){
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if(newNode == NULL){
        printf("할당 오류\n");
        exit(1);
    }
    memset(newNode, 0, sizeof(NODE));
    newNode->data = data;

    NODE *prev = list->tail->prev;

    newNode->next = list->tail;
    newNode->prev = prev;

    prev->next = newNode;
    list->tail->prev = newNode;
}

// 맨 앞 삭제
void RemoveFront(LIST *list){
    if(list->head->next == list->tail) return;
    NODE *del = list->head->next;

    list->head->next = del->next;
    del->next->prev = list->head;

    // 삭제될 노드 출력 
    printf("[%p]\t%d\t[%p]\t[%p]\n", del, del->data, del->next, del->prev);
    free(del);
}

// 맨 뒤 삭제
void RemoveRear(LIST *list){
    if(list->head->next == list->tail) return;

    NODE *del = list->tail->prev;

    list->tail->prev = del->prev;
    del->prev->next = list->tail;
        
    // 삭제될 노드 출력 
    printf("[%p]\t%d\t[%p]\t[%p]\n", del, del->data, del->next, del->prev);
    free(del);
}

// 선택 노드 제거
void RemoveByValue(LIST *list, int data){
    if(list->head->next == list->tail) return;

    NODE *cur = list->head->next;

    while(cur != list->tail){
        if(cur->data == data){
            cur->next->prev = cur->prev;
            cur->prev->next = cur->next;
            
            // 삭제될 노드 출력 
            printf("[%p]\t%d\t[%p]\t[%p]\n", cur, cur->data, cur->next, cur->prev);
            free(cur);
            return;
        }
    }
    printf("해당 사항 없음\n");
}

// 선택 노드 출력
void PrintNode(LIST *list, int data){
    if(list->head->next == list->tail) return;

    NODE *cur = list->head->next;

    while(cur != list->tail){
        if(cur->data == data){
            printf("[%p]\t%d\t[%p]\t[%p]\n", cur, cur->data, cur->next, cur->prev);
            return;
        }
        cur = cur->next;
    }
    printf("해당 사항 없음\n");
}

// 역방향 출력
void PrintReverse(LIST *list){
    if(list->head->next == list->tail) return;
    NODE *cur = list->tail->prev;

    while(cur != list->head){
        printf("[%p]\t%d\t[%p]\t[%p]\n", cur, cur->data, cur->next, cur->prev);
        cur = cur->prev;
    }
}

// 전체 출력
void PrintAll(LIST *list){
    if(list->head->next == list->tail) return; 
    NODE *cur = list->head->next;

    while(cur != list->tail){
        printf("[%p]\t%d\t[%p]\t[%p]\n", cur, cur->data, cur->next, cur->prev);
        cur = cur->next;
    }
}

// 전체 삭제
void ClearList(LIST *list){
    if(list->head->next == list->tail) return;

    NODE *cur = list->head->next;
    while(cur != list->tail){
        NODE *del = cur;
        cur = cur->next;

        free(del);
    }
    list->head->next = list->tail;
    list->tail->prev = list->head;
    printf("제거 완료\n");
}

// 완전 제거
void Terminate(LIST *list){
    ClearList(list);
    free(list->head);
    free(list->tail);

}





// 더미 데이터
void DummyData(LIST *list){
    AddNode(list, 1);
    AddNode(list, 2);
    AddNode(list, 3);
}


