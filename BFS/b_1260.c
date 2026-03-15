/** 
 * 데이터:
 * - 입력
 *      - N: 정점의 개수
 *      - M: 간선의 개수
 *      - V: 시작할 정점 번호 
 * 1260, 2178, 2606, 2667, 7576, 1697, 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int max;
    int num;
    int front;
    int rear;
    int *que;
}Queue;

void BFS(int start, int n, int *visited, int **graph);
int Queue_Init(Queue *q, int n);
int Queue_Enqueue(Queue *q, int x);
int Queue_Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);


int main(int argc, char *argv[]){
    //입력받기


    int n = 5;
    int m = 5;
    int start = 0;
    
    int **graph = (int **)malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++){
        graph[i] = (int *)calloc(n, sizeof(int));
    }

    graph[0][1] = graph[1][0] = 1;
    graph[0][3] = graph[3][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[1][4] = graph[4][1] = 1;
    graph[3][4] = graph[4][3] = 1;

    int *visited = (int *)calloc(n, sizeof(int));

    BFS(0, n, visited, graph);
    
    for(int i = 0; i < n; i++) free(graph[i]);
    free(graph);
    free(visited);

    return 0;

}

void BFS(int start, int n, int *visited, int **graph){
    Queue q;
    Queue_Init(&q, n);
    Queue_Enqueue(&q, start);
    visited[start] = 1;

    while(!Queue_IsEmpty(&q)){
        int v;
        Queue_Dequeue(&q, &v);
        printf("%d ", v);

        for(int i = 0; i < n; i++){
            if(graph[v][i] && !visited[i]){
                Queue_Enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    Queue_Terminate(&q);
}

int Queue_Init(Queue *q, int n){
    q->que = (int *)malloc(sizeof(int) * n);
    if(q->que == NULL){q->max = 0; return -1;}
    q->front = q->rear = q->num = 0;
    q->max = n;
    return 0;
}

int Queue_Enqueue(Queue *q, int x){
    if(q->num >= q->max) return -1;
    else{
        q->que[q->rear++] = x;
        if(q->rear == q->max) q->rear = 0;
        q->num++;
        return 0;
    }
}

int Queue_Dequeue(Queue *q, int *x){
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