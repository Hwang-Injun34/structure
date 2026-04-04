#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


// 초기화
void InitList(LIST *list){
    list->head = (NODE *)malloc(sizeof(NODE));
    if(list->head == NULL){
        printf("할당 오류\n");
        exit(1);
    }
    memset(list->head, 0, sizeof(NODE));
    list->head->next = NULL;

    list->tail = list->head;
}

// 머리 삽입
void InsertFront(LIST *list, int data){
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if(newNode == NULL) return;
    memset(newNode, 0, sizeof(NODE));

    newNode->data = data;
    newNode->next = list->head->next;
    list->head->next = newNode;

    if(list->tail == list->head){
        list->tail = newNode;
    }
}

// 꼬리에 삽입
void InsertRear(LIST *list, int data){
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if(newNode == NULL) return;
    memset(newNode, 0, sizeof(NODE));

    newNode->data = data;
    newNode->next = NULL;

    list->tail->next = newNode;
    list->tail = newNode;
}

// 선택 출력
void PrintNode(LIST *list, int data){
    NODE *cur = list->head->next;

    while(cur != NULL){
        if(cur->data == data){
            printf("[%p]\t%d\t[%p]\n", cur, cur->data, cur->next);
            return;
        }
        cur = cur->next;
    }
    printf("해당 사항 없음\n");
}

// 전체 출력
void PrintAll(LIST *list){
    NODE *cur = list->head->next;

    while(cur != NULL){
        printf("[%p]\t%d\t[%p]\n", cur, cur->data, cur->next);
        cur = cur->next;
    }
}

// 머리 삭제
void RemoveFront(LIST *list){
    if(list->head->next == NULL) return;

    NODE *del = list->head->next;
    list->head->next = del->next;
    
    if(del == list->tail){
        list->tail = list->head;
    }

    printf("[%p]\t%d\t[%p]\n", del, del->data, del->next); 
    free(del);
}

// 꼬리 삭제
void RemoveRear(LIST *list){
    if(list->head->next == NULL) return;

    NODE *prev = list->head;
    NODE *cur = list->head->next;

    while(cur->next != NULL){
        prev = cur;
        cur = cur->next;
    }

    printf("[%p]\t%d\t[%p]\n", cur, cur->data, cur->next);
    prev->next = NULL;
    list->tail = prev;
    free(cur);
}

// 선택 제거
void RemoveByValue(LIST *list, int data){
    NODE *prev = list->head;
    NODE *cur = list->head->next;

    while(cur != NULL){
        if(cur->data == data){
            prev->next = cur->next;

            if(cur == list->tail){
                list->tail = prev;
            }
            printf("[%p]\t%d\t[%p]\n", cur, cur->data, cur->next);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("해당 사항 없음\n");
}


// 전체 삭제
void ClearList(LIST *list){
    NODE *cur = list->head->next; 

    while(cur != NULL){
        NODE *del = cur;
        cur = cur->next;
        free(del);
    }
    list->head->next = NULL;
    list->tail = list->head;
}


// 완전 제거
void Terminate(LIST *list){
    ClearList(list);
    free(list->head);
}

// 더미 데이터
void DummyDataFront(LIST *list){
    InsertFront(list, 1);
    InsertFront(list, 2);
    InsertFront(list, 3);
}

void DummyDataRear(LIST *list){
    InsertRear(list, 1);
    InsertRear(list, 2);
    InsertRear(list, 3);
}