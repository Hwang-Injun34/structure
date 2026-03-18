/**
 * 붙어있는 주택의 단지 수 세기
 * - 오름차순으로 정렬 후 반환
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

int Queue_Init(Queue *q, int n);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);
int BFS(int **graph, int **visited, int n, int start);

int main(int argc, char *argv[]){

    int n = 7;
    int house[7][7] = {
        {0,1,1,0,1,0,0},
        {0,1,1,0,1,0,1},
        {1,1,1,0,1,0,1},
        {0,0,0,0,1,1,1},
        {0,1,0,0,0,0,0},
        {0,1,1,1,1,1,0},
        {0,1,1,1,0,0,0}
    };

    int index = 0;
    int *result = (int *)malloc(sizeof(int) * (n * n / 2));

    int **visited = (int **)malloc(sizeof(int *) * n);
    int **graph = (int **)malloc(sizeof(int *) * n);
    
    for(int i = 0; i < n; i++){
        graph[i] = (int *)calloc(n, sizeof(int));
        visited[i] = (int *)calloc(n, sizeof(int));
        for(int j = 0; j < n; j++){
            graph[i][j] = house[i][j];
        }
    }
    
    // 모든 배열을 순회 - BFS 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(graph[i][j] && !visited[i][j]){
                result[index++] = BFS(graph, visited, n, i * n + j);
            }
        }
    }

    // 오름차순 정렬(버블 정렬)
    for(int i = 0; i < index - 1; i++){
        for(int j = 0; j < index - i - 1; j++){
            if(result[j] > result[j + 1]){
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }


    // 출력
    for(int i = 0; i < index; i++) printf("%d ", result[i]);
    printf("\n");

    // 힙 해제
    for(int i = 0; i < n; i++) {free(graph[i]); free(visited[i]);}
    free(graph);
    free(visited);

    return 0;
}

int BFS(int **graph, int **visited, int n, int start){
    // 단지 체크
    int count = 1;
    
    // 방향
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 위치
    int x = start / n;
    int y = start % n;
    
    Queue q;

    Queue_Init(&q, n * n);
    Enqueue(&q, start);

    visited[x][y] = 1;

    while(!Queue_IsEmpty(&q)){
        int pos;
        Dequeue(&q, &pos); 
        x = pos / n;
        y = pos % n;
        
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(!graph[nx][ny]) continue;
            if(visited[nx][ny]) continue;
            
            visited[nx][ny] = 1;
            Enqueue(&q, nx * n + ny);
            count++;
        }
    }
    Queue_Terminate(&q);
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