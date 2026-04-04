#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"


// 큐 초기화
void Init(QUEUE *q, int max){
    q->front = q->rear = q->num = 0;
    q->que = (int *)malloc(sizeof(int) * max);
    if(q->que == NULL){
        q->max = 0;
        // 큐 할당 실패
        printf("할당 오류\n");
        exit(1);
    }

    q->max = max;
    return;
}

// 인큐
void Enqueue(QUEUE *q, int data){
    if(q->num >= q->max) {
        printf("삽입 불가");
        return;
    }

    q->que[q->rear++] = data; 

    if(q->rear == q->max) q->rear = 0;
    q->num++;
    return;
}

// 디큐
void Dequeue(QUEUE *q, int *data){
    if(q->num <= 0) {
        printf("데이터 없음");
        return;
    }
    *data = q->que[q->front++];
    if(q->front == q->max) q->front = 0;
    q->num--;
    return;
}

// 전체 출력
void PrintAll(QUEUE *q){
    if(IsEmpty(q)){
        printf("비어 있음\n");
        return;
    }

    int idx = q->front; 
    printf("Front -> ");
    for(int i = 0; i < q->num; i++){
        printf("(%d) ", q->que[idx]);
        idx++;
        if(idx == q->max) idx = 0;
    }
    printf(" <- Rear");
    printf("\n");
}


// 비어있는지 체크
int IsEmpty(const QUEUE *q){
    return q->num == 0;
}


// 종료
void Terminate(QUEUE *q){
    if(q->que != NULL){
        free(q->que);
    }

    q->front = q->rear = q->max = q->num = 0;
}



// 더미 데이터
void DummyData(QUEUE *q){
    Enqueue(q, 1);
    Enqueue(q, 2);
    Enqueue(q, 3);
}




