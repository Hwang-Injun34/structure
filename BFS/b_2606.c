/**
 * 바이러스
 * 노드 형태로 주어진 컴퓨터가 연결되어 있으면 점차 퍼져나가면서 감염됨
 * 총 감염된 컴퓨터의 수를 반환
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int max;
    int num;
    int front;
    int rear;
    int *que;
} Queue;

int BFS(int **graph, int start, int n, int m);
int Queue_Init(Queue *q, int n);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);

int main(int argc, char *argv[]){

    int n = 7; 
    int m = 6;

    int **graph = (int **)malloc(sizeof(int *) * (n + 1));
    for(int i = 0; i < n+1; i++){
        graph[i] = (int *)calloc(n+1, sizeof(int));
    }

    graph[1][2] = graph[2][1] = 1;
    graph[1][5] = graph[5][1] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[5][2] = graph[2][5] = 1;
    graph[5][6] = graph[6][5] = 1;
    graph[4][7] = graph[7][4] = 1;

    int answer = BFS(graph, 1, n, m);
    printf("감염된 컴퓨터: %d\n", answer);
    fflush(stdout);

    for(int i = 0; i < n + 1; i++){
        free(graph[i]);
    }
    free(graph);

    return 0;
}

int BFS(int **graph, int start, int n, int m){
    int count = 0;
    int max = (n + 1) * (m + 1);
    
    Queue q;

    Queue_Init(&q, max);
    Enqueue(&q, start);

    int *visited = (int *)malloc(sizeof(int) * n+1);

    while(!Queue_IsEmpty(&q)){
        int v;
        Dequeue(&q, &v);
        visited[v] = 1;

        for(int i = 0; i < n + 1; i++){
            if(graph[v][i] == 1 && !visited[i]){
                count++;
                Enqueue(&q, i);
                visited[v] = 1;
            }

            if(count == m){
                free(visited);
                return count;
            }
        }
    }

    Queue_Terminate(&q);
    free(visited);
    return count;
}

int Queue_Init(Queue *q, int n){
    q->front = q->rear = q->num = 0;
    q->que = (int *)malloc(sizeof(int) * n);
    if(q->que == NULL) {q->max = 0; return -1;}
    q->max = n;
    return 0;
}

int Enqueue(Queue *q, int x){
    if(q->num >= q->max) return -1;
    q->que[q->rear++] = x;
    if(q->rear == q->max) q->rear = 0;
    q->num++;
    return 0;
}

int Dequeue(Queue *q, int *x){
    if(q->num <= 0) return -1;
    *x = q->que[q->front++];
    if(q->front == q->max) q->front = 0;
    q->num--;
    return 0;
}

int Queue_IsEmpty(const Queue *q){
    return q->num == 0;
}

void Queue_Terminate(Queue *q){
    if(q->que != NULL) free(q->que);
    q->front = q->rear = q->num = q->max = 0;
}