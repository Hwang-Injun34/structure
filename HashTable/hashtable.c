#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

// 초기화
void InitTable(HASHTABLE *ht){
    for(int i = 0; i < TABLE_SIZE; i++){
        ht->table[i] = NULL;
    }
}

// 해시 함수
int HashFunc(int key){
    return key % TABLE_SIZE;
}


// 머리 삽입
void Insert(HASHTABLE *ht, int key, int value){
    int index = HashFunc(key);

    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    //head insert
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}


// 삭제
void Delete(HASHTABLE *ht, int key){
    int index = HashFunc(key);

    NODE *cur = ht->table[index];
    NODE *prev = NULL;

    while(cur != NULL){
        if(cur->key == key){
            if(prev == NULL){
                ht->table[index] = cur->next;
            }
            else{
                prev->next = cur->next;
            }
            printf("[%p]\t(%d:%d)\t[%p]\n", cur, cur->key, cur->value, cur->next);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

//전체 출력
void PrintTable(HASHTABLE *ht){
    for(int i = 0; i < TABLE_SIZE; i++){
        NODE *cur = ht->table[i];
        
        while(cur != NULL){
            printf("[%p]\t(%d:%d)\t[%p]\n", cur, cur->key, cur->value, cur->next);
            cur = cur->next;
        }
        printf("\n");
    }
}

// 검색
void Search(HASHTABLE *ht, int key){
    int index = HashFunc(key);

    NODE *cur = ht->table[index];

    while(cur != NULL){
        if(cur->key == key){
            printf("[%p]\t(%d:%d)\t[%p]\n", cur, cur->key, cur->value, cur->next);
            return;
        }
        cur = cur->next;
    }
    printf("해당 사항 없음\n");
}


// 전체 삭제
void ClearTable(HASHTABLE *ht){
    for(int i = 0; i < TABLE_SIZE; i++){
        NODE *cur = ht->table[i];

        while(cur != NULL){
            NODE *del = cur;
            cur= cur->next;
            free(del);
        }
        ht->table[i] = NULL;
    }
}



// 더미 데이터
void DummyData(HASHTABLE *ht){
    Insert(ht, 1, 1);
    Insert(ht, 11, 2);
    Insert(ht, 21, 3);

    Insert(ht, 2, 1);
    Insert(ht, 12, 2);
    Insert(ht, 22, 3);

    Insert(ht, 3, 1);
    Insert(ht, 13, 2);
    Insert(ht, 23, 3);

    Insert(ht, 4, 1);
    Insert(ht, 14, 2);
    Insert(ht, 24, 3);
}