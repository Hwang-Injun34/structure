/**
 * 데이터:
 * - 도착:(N, M)
 * - 1: 이동, 0: 이동 불가
 * - 출발:(1, 1)
 * 
 * 조건:
 * - (1,1)부터 도착지점까지 이동한 횟수를 카운트하여 반환
 * - 최소 방문
 */

#include <stdio.h>
#include <stdlib.h>
    
typedef struct {
    int max; 
    int num;
    int front;
    int rear;
    int *que;
}Queue; 

int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);

int BFS(int **graph, int n, int m);


int main(int argc, char *argv[]){
    
    // 입력받기
    int n = 4;
    int m = 6;

    int maze[4][6] = {
        {1, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1}
    };

    int **graph = (int **)malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++){
        graph[i] = (int *)malloc(sizeof(int) * m);
        for(int j = 0; j < m; j++){
            graph[i][j] = maze[i][j];
        }
    }

    // BFS
    int answer = BFS(graph, n, m);

    printf("최소 이동 칸 수: %d\n", answer);

    for(int i = 0; i < n; i++) free(graph[i]);
    free(graph);

    return 0;
}

int BFS(int **graph, int n, int m){
    int dx[4] = {-1, 1, 0 , 0}; // 위, 아래, 좌, 우
    int dy[4] = {0, 0, -1, 1};

    int **visited = (int**)malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++){
        visited[i] = (int *)calloc(m, sizeof(int));
    }

    Queue q;
    Queue_Init(&q, n * m);
    Enqueue(&q, 0); // (0, 0)

    // if(graph[0][0] == 0) return 0;
    visited[0][0] = 1;

    while(!Queue_IsEmpty(&q)){
        int pos;
        Dequeue(&q, &pos);

        int x = pos / m;
        int y = pos % m;
        
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i]; 
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if(graph[nx][ny] == 0) continue;
            if(visited[nx][ny] != 0) continue;
            // if(nx == n-1 && ny == m-1) return visited[x][y] + 1;

            visited[nx][ny] = visited[x][y] + 1;

            Enqueue(&q, nx * m + ny);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d  ", visited[i][j]);
        }
        printf("\n");
    }

    int result = visited[n - 1][m -1];
    for(int i = 0; i < n; i++) free(visited[i]);
    free(visited);

    Queue_Terminate(&q);

    return result;

}

int Queue_Init(Queue *q, int max){
    q->front = q->rear = q->num = 0;
    q->que = (int *)malloc(sizeof(int) * max);
    
    if(q->que == NULL) {q->max = max; return -1;}
    
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
    q->front = q->max = q->num = q->rear = 0;
}