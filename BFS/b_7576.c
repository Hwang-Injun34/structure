/*
[백준] 7576 
[문제]
철수의 토마토 농장에서는 토마토를 보관하는 큰 창고를 가지고 있다. 
토마토는 아래의 그림과 같이 격자 모양의 상자 칸에 하나씩 넣어서 창고에 보관한다. 

창고에 보관되는 토마토들 중에는 잘 익은 것도 있지만, 아직 익지 않은 토마토들도 있을 수 있다. 
보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받게 된다. 
하나의 토마토의 인접한 곳은 왼쪽, 오른쪽, 앞, 뒤, 네 방향에 있는 토마토를 의미한다. 

대각선 방향에 있는 토마토들에게는 영향을 주지 못하며, 토마토가 혼하 저절로 익는 경우는 없다고 가정한다. 
철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지, 그 최소 일 수를 알고 싶어 한다. 

토마토를 창고에 보관하는 격자 모양의 상자들의 크기와 익은 토마토들과 익지 않은 토마토들의 정보가 주어졌을 때, 
며칠이 지나면 토마토들이 모두 익는지, 그 최소 일수를 구하는 프로그램을 작성하라. 
단, 상자의 일부 칸에는 토마토가 들어있지 않을 수 있다. 

[입력]
6 4
0 -1 0 0 0 0
-1 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 1

[의사코드]
status: 
    x, y

transition: 
처음 시작 시에 토마토가 들어 있는 위치를 모두 큐에다가 삽입

    - 방향: (x, y) -> (nx, ny)
    - 조건: 0인 토마토가 graph[nx][ny]라면 여기에 graph[x][y] + 1 저장

end:
    - 가장 큰 max 값을 반환
    - 만약 0이 있을 경우 return -1

[출력]
토마토가 모두 익을 때까지의 최소 날짜 출력
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

int BFS(int **graph, int n, int m);

int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);

int main(int argc, char *argv[]){
    // 입력
    int n = 4;
    int m = 6; 

    // 토마토 박스 
    int tomato[4][6] = {
        {0, -1, 0, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1}
    };

    // 메모리 할당 및 복사
    int **graph = (int **)malloc(sizeof(int *) * n);
    
    for(int i = 0; i < n; i++){
        graph[i] = (int *)malloc(sizeof(int) * m);
        
        for(int j = 0; j < m; j++){
            graph[i][j] = tomato[i][j];
        }
    }
    
    // BFS
    int answer = BFS(graph, n, m);

    // 결과 출력
    printf("%d\n", answer);

    // 메모리 해제
    for(int i = 0; i < n; i++){
        free(graph[i]);
    }
    free(graph);

    return 0;
}

int BFS(int **graph, int n, int m){
    // 방향
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 큐 
    Queue q;
    Queue_Init(&q, n * m);

    // 익은 토마토 삽입
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(graph[i][j] == 1){
                Enqueue(&q, i * m + j);
            }
        }
    }

    while(!Queue_IsEmpty(&q)){
        int pos;
        Dequeue(&q, &pos);

        int x = pos / m;
        int y = pos % m;

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue; 
            if(graph[nx][ny] != 0) continue;

            graph[nx][ny] = graph[x][y] + 1; 
            Enqueue(&q, nx * m + ny);
        }
    }

    int max = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(graph[i][j] == 0) {
                Queue_Terminate(&q);
                return -1;
            }
            if(max < graph[i][j]){
                max = graph[i][j];
            }
        }
    }

    Queue_Terminate(&q);
    return max - 1;
}

int Queue_Init(Queue *q, int max){
    q->front = q->rear = q->num = 0;

    q->que = (int *)malloc(sizeof(int)* max);
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
    q->max = q->front = q->rear = q->num = 0;

}