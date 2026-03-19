/*
[백준] 2606
[문제] 
신종 바이러스인 웜 바이러스는 네트워크를 통해 전파된다. 
한 컴퓨터가 웜 바이러스에 걸리면 그 컴퓨터와 네트워크 상에서 연결되어 있는 모든 컴퓨터는 웜 바이러스에 걸리게 된다. 

예를 들어 7대의 컴퓨터가 <그림>과 같이 네트워크 상에 연결되어 있다고 하자. 
1번 컴퓨터가 웜 바이러스에 걸리면 웜 바이러스는 2번과 5번 컴퓨터를 거쳐 3번과 6번 컴퓨터까지 전파되어 2, 3, 5, 6 네 대의 컴퓨터는 웜 바이러스에 걸리게 된다. 

하지만 4번과 7번 컴퓨터는 1번 컴퓨터와 네트워크 상에서 연결되어 있지 않기 때문에 영향을 받지 않는다. 

어느날 1번 컴퓨터가 웜 바이러스에 걸렸다. 
컴퓨터의 수와 네트워크 상에서 서로 연결되어 있는 정보가 주어질 때, 
1번 컴퓨터를 통해 웜 바이러스에 걸리게 되는 컴퓨터의 수를 출력하는 프로그램을 작성하시오. 

[입력]
7
6
1 2
2 3
1 5
5 2
5 6
4 7

[의사코드]
status:
    현재 노드

transition: 
    현재 노드와 연결된 노드로 이동
    visited 표시(감염)

end: 
    큐가 비었을 때(더이상 연결이 없음)

[출력]
감염된 컴퓨터 수

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

int BFS(int **graph, int n, int m);
int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);


int main(int argc, char *argv[]){
    
    //입력값
    int n = 7; 
    int m = 6;

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * (n + 1));
    for(int i = 0; i < n + 1; i++){
        graph[i] = (int *)calloc(n + 1, sizeof(int));
    }

    graph[1][2] = graph[2][1] = 1;
    graph[1][5] = graph[5][1] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[5][2] = graph[2][5] = 1;
    graph[5][6] = graph[6][5] = 1;
    graph[4][7] = graph[7][4] = 1;

    // BFS
    int answer = BFS(graph, n, m);

    // 결과 출력
    printf("%d\n", answer);

    // 메모리 해제
    for(int i = 0; i < n+1; i++) free(graph[i]);
    free(graph);

    return 0;
}

int BFS(int **graph, int n, int m){
    int count =  0;

    // 방문 체크
    int *visited = (int *)calloc(n+1, sizeof(int));

    // 큐
    Queue q;
    Queue_Init(&q, n+1);

    Enqueue(&q, 1);
    visited[1] = 1;

    while(!Queue_IsEmpty(&q)){
        int v;
        Dequeue(&q, &v);
        visited[v] = 1;

        for(int i = 0; i < n+1; i++){
            if(graph[v][i] == 1 && visited[i] == 0){
                Enqueue(&q, i);
                visited[i] = 1;
                count++;
            }
        }
    }

    Queue_Terminate(&q);
    free(visited);

    // 결과 반환
    return count;

}

int Queue_Init(Queue *q, int max){
    q->front = q->rear = q->num = 0;
    q->que = (int *)malloc(sizeof(int *) * max);

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