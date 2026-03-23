/*
[프로그래머스] 네트워크
[문제]
네트워크란 컴퓨터 상호 간에 정보를 교환할 수 있도록 연결된 형태를 의미합니다. 
예를 들어, 컴퓨터 A와 컴퓨터 B가 직접적으로 연결되어 있고, 
컴퓨터 B와 컴퓨터 C가 직접적으로 연결되어 있을 때, 
컴퓨터 A와 C도 간접적으로 연결되어 정보를 교환할 수 있습니다. 

따라서 A, B, C는 모두 같은 네트워크 상에 있다고 할 수 있습니다. 

컴퓨터의 개수 n, 연결에 대한 정보가 담긴 2차원 배열 computers가 매개변수로 주어질 때, 네트워크의 개수를 return 하시오. 

[입력]
n: 3	
computers[][]: [[1, 1, 0], [1, 1, 0], [0, 0, 1]]

[의사코드]
states: 
    x 
transition: 
    방문
    [x][i] -> [i][j] -> [j][i] 로 연결 체크

end:
    전체 노드 순회 후 종료


*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    int *que;
} Queue;

void BFS(int **graph, int *visited, int n, int start);
int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);

int main(int argc, char *argv[]){
    // 입력
    int n = 3;
    int computers[3][3] = {
        {1, 1, 0}, 
        {1, 1, 0}, 
        {0, 0, 1}
    };

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++){
        graph[i] = (int *)calloc(n, sizeof(int));
        for(int j = 0; j < n; j++) graph[i][j] = computers[i][j];
    }

    // 방문
    int *visited = (int *)calloc(n, sizeof(int));

    int count = 0; 

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            BFS(graph, visited, n, i);
            count++;
        }
    }

    printf("%d\n", count);

    // 메모리 해제
    for(int i = 0; i < n; i++) free(graph[i]);
    free(graph);
    free(visited);

    return 0;
}

void BFS(int **graph, int *visited, int n, int start){
    // 큐 선언 및 초기화
    Queue q;

    Queue_Init(&q, n);
    Enqueue(&q, start);
    visited[start] = 1;

    while(!Queue_IsEmpty(&q)){
        int v;
        Dequeue(&q, &v);

        for(int i = 0; i < n; i++){
            if(graph[v][i] == 1 && !visited[i]){
                Enqueue(&q, i); 
                visited[i] = 1;
            }
        }

    }

    Queue_Terminate(&q);
}


int Queue_Init(Queue *q, int max){
    q->front = q->rear = q->num = 0;
    q->que = (int *)malloc(sizeof(int) * max);

    if(q->que == NULL){
        q->max = 0;
        return -1;
    }
    
    q->max = max;
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