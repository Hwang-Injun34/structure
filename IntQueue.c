#include "IntQueue.h"
#include <stdio.h>
#include <stdlib.h>

// -- 큐 초기화 -- 
int IntQueue_Init(IntQueue *q, int max){
    q->num = q->front = q->rear = 0;

    if((q->que = (int *)calloc(max, sizeof(int))) == NULL){
        q->max = 0;
        return -1;
    }
    q->max = max;
    return 0;
}

// -- 인큐 -- 
int IntQueue_Enqueue(IntQueue *q, int x){
    if(q->num > q->max) return -1; 
    else{
        q->num++;
        q->que[q->rear++] = x;

        if(q-> rear == q->max) q->rear = 0; 
        return 0;
    }
}

// -- 디큐 --
int InitQueue_Dequeue(IntQueue *q, int *x){
    if(q->num <= 0) return -1;
    else{
        q->num--;
        *x = q->que[q->front++];
        if(q->front == q->max) q->front=0; 
        return 0;
    }
}

// -- 피크 -- 
int IntQueue_Peek(const IntQueue *q, int *x){
    if(q->num <= 0) return -1;
    *x = q->que[q->front];
    return 0;
}

// -- 모든 데이터 삭제 -- 
void IntQueue_Clear(IntQueue *q){
    q->front = q->rear = q->num = 0;
}

// -- 큐의 최대 용량 --
int IntQueue_Capacity(const IntQueue *q){
    return q->max;
}

// -- 큐에 쌓여 있는 데이터 개수 -- 
int IntQueue_Size(const IntQueue *q){
    return q->num;
}

// -- 큐가 비어있는지 검사 -- 
int IntQueue_isEmpty(const IntQueue *q){
    return q->num <= 0;
}

// -- 큐가 가득 차 있는지 --
int IntQueue_isFull(const IntQueue *q){
    return q->num >= q->max;
}

// -- 큐에서 검색 -- 
int IntQueue_Search(const IntQueue *q, int x){
    for(int i = 0; i < q->num; i++){
        int idx = (i + q->front) % q->max;
        if(q->que[idx] == x) return idx;
    }
    return -1;
}

// -- 모든 데이터 출력 --
void IntQueue_Print(const IntQueue *q){
    for(int i = 0; i < q->num; i++) printf("%d ", q->que[(i+q->front) % q->max]);
    putchar('\n');
}

// -- 큐의 종료 -- 
void IntQueue_Terminate(IntQueue *q){
    if(q->que != NULL) free(q->que);

    q->max = q->num = q->front = q->rear = 0;
}