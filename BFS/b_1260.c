/** 
[백준] 1260번
[문제]
그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오. 
단, 방문할 수 있는 장점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문하고, 더 이상 방문할 수 있는 점이 없는 경우 종료한다. 
정점 번호는 1번부터 N번까지다. 

[입력]
4 5 1
1 2
1 3
1 4
2 4
3 4
정점 개수: 4, 간선의 개수 5, 시작 정점 1
노드의 시작이 0이아닌 1이라는 점에 주의

[의사 코드]
state: 
    cur_node

transition:
    cur_node -> next_node
        1. 연결되어 있어야함
        2. 방문한적 없어야함
        
end: 
    큐가 비어 있으면 종료    
    노드를 전부 순회하면 종료

[출력]
방문한 순서대로 출력

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

void BFS(int **graph, int n, int start, int *result);

int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);


int main(int argc, char *argv[]){
    // 입력 값
    int n = 4; // 노드 개수
    int m = 5; // 연결 수
    int start = 0; // 노드 1 (-1)

    // 결과
    int result[4];

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++){
        graph[i] = (int *)calloc(n, sizeof(int));
    }

    // 연결
    graph[0][1] = graph[1][0] = 1;
    graph[0][2] = graph[2][0] = 1;
    graph[0][3] = graph[3][0] = 1;
    graph[1][3] = graph[3][1] = 1;
    graph[2][3] = graph[3][2] = 1;

    // BFS 
    BFS(graph, n, start, result);

    // 결과 출력
    for(int i = 0; i < n; i++) printf("%d ", result[i]);
    printf("\n");

    // 메모리 해제
    for(int i = 0; i < n; i++) free(graph[i]);
    free(graph);

    return 0;
}

void BFS(int **graph, int n, int start, int *result){
    int index = 0;
    // 방문 체크
    int *visited = (int *)calloc(n, sizeof(int));

    // 큐 선언
    Queue q;
    Queue_Init(&q, n);

    Enqueue(&q, start);
    visited[start] = 1;

    while(!Queue_IsEmpty(&q)){
        int v;
        Dequeue(&q, &v);
        result[index++] = v + 1;

        for(int i = 0; i < n; i++){
            if(graph[v][i] != 1) continue;  // 연결되어 있지 않으면 패스,
            if(visited[i] == 1) continue;   // 방문했으면 패스
            Enqueue(&q, i); 
            visited[i] = 1;
        }
    }

    // 메모리 해제
    free(visited);
    Queue_Terminate(&q);
}

int Queue_Init(Queue *q, int max){
    q->front = q->rear = q->num = 0;
    q->que = (int *)malloc(sizeof(int) * max);

    if(q->que == NULL) {q->max = 0; return -1;}
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