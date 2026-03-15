// #include "IntQueue.h"
#include <stdio.h>
#include <stdlib.h>


// 구조체 선언 - 배열 형태
typedef struct {
    int max;
    int num;
    int front;
    int rear;
    int *que;
}IntQueue;

// 큐 초기화
int IntQueue_Init(IntQueue *q, int max){
    q->front = q->rear = q->num = 0;
    q->que = (int *)calloc(max, sizeof(int));
    if(q->que == NULL) q->max=0; return -1;
    
    q->max = max;
    return 0;
}
// 큐 IsEmpty 
int IntQueue_isEmpty(const IntQueue *q){
    return q->num == 0;
}

// 인큐
int IntQueue_Enqueue(IntQueue *q, int x){
    if(q->num >= q->max) return -1;
    else{
        q->que[q->rear++] = x;
        if(q->rear == q->max) q->rear = 0;
        q->num++;
        return 0;
    }
    q->num++;
}
        


// 디큐
int IntQueue_Dequeue(IntQueue *q, int *x){
    if(q->num <= 0) return -1;
    else{
        q->num--;
        *x = q->que[q->front++];
        
        if(q->front == q->max) q->front = 0;
        return 0;
    }
}

// 종료
void IntQueue_Terminate(IntQueue *q){
    if(q->que != NULL) free(q->que);

    q->max = q->num = q->front = q->rear = 0;
}

#define MAX 100 
int graph[MAX][MAX];
int visited[MAX];
int n; // 정점 노드의 개수

void BFS(int start){
    IntQueue q;
    IntQueue_Init(&q, MAX);

    IntQueue_Enqueue(&q, start);
    visited[start] = 1;
    while(!IntQueue_isEmpty(&q)){
        int v;
        IntQueue_Dequeue(&q, &v);
        printf("%d ", v);
        
        for(int i = 0; i < n; i++){
            if(graph[v][i] && !visited[i]){
                IntQueue_Enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
    IntQueue_Terminate(&q);

}
