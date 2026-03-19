/**
[백준] 2178
[문제]
N x M 크기의 배열로 표현되는 미로가 있다. 

미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 
이러한 미로가 주어졌을 때, (1, 1)에서 출발하여 (N, M)의 위치로 이동할 때 지나야하는 최소의 칸 수를 구하는 프로그램을 작성하시오. 

한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다. 

[입력]
4 6
101111
101010
101011
111011

[출력]
최소의 칸 수를 출력

[의사코드]
* 해당 좌표가 (1, 1)이지만 나는 (0, 0)으로 잡음
status:
    (x, y) 

transition:
    (x, y) -> (nx, ny)로 이동
        - graph[nx][ny] == 1
        - graph[nx][ny] = graph[x][y] + 1
    
end:
    - (x, y) == (n-1, m-1)
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
void Queue_Terminate(Queue *Q);

int main(int argc, char *argv[]){
    // 입력값
    int n = 4;
    int m = 6;

    int maze[4][6] = {
        {1, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1}
    };

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(sizeof(int) * m);
        
        for(int j = 0; j < m; j++){
            graph[i][j] = maze[i][j]; 
        }
    }
    
    // BFS
    int answer = BFS(graph, n, m);

    // 결과 출력
    printf("%d\n", answer);

    // 메모리 해제
    for(int i = 0; i < n; i++) free(graph[i]);
    free(graph);

    return 0;
}

int BFS(int **graph, int n, int m){
    // 방향
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 큐
    Queue q;

    Queue_Init(&q, n*m);
    Enqueue(&q, 0); // x * m + y
    
    while(!Queue_IsEmpty(&q)){
        int pos;
        Dequeue(&q, &pos);
        
        // x, y 좌표 계산
        int x = pos / m;
        int y = pos % m;
        
        // 다음 좌표
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if(graph[nx][ny] == 1) {
                Enqueue(&q, nx * m + ny);
                graph[nx][ny] = graph[x][y] + 1;
            }
        }
    }

    Queue_Terminate(&q);
    return graph[n-1][m-1];

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
    q->front = q->rear = q->max = q->num = 0;
}