/*
[백준] 2667
[문제]
<그림>과 같이 정사각형 모양의 지도가 있다. 
1은 집이 있는 곳을 0은 집이 없는 곳을 나타낸다. 
철수는 이 지도를 가지고 연결된 집의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 
여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 

대각선상에 집이 있는 경우는 연결된 것이 아니다. 

지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.

[입력]
7
0110100
0110101
1110101
0000111
0100000
0111110
0111000

[의사코드]
status: 
    x, y

transition:
    전부 순회(graph에서 1과 방문하지 않았을 시)

    방향:  x, y -> nx, ny
        - 방향, graph == 1, visited == 0인 경우에만 카운트

end: 
    전부 순회가 되어야 종료

[출력]
각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력

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


int BFS(int **graph, int **visited, int n, int start);
int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *Q);

int main(int argc, char *argv[]){
    
    // 입력값
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

    int **graph = (int **)malloc(sizeof(int *) * n);
    int **visited = (int **)malloc(sizeof(int *) * n);

    for(int i = 0; i < n; i++){
        graph[i] = (int *)calloc(n, sizeof(int));
        visited[i] = (int *)calloc(n, sizeof(int));

        for(int j = 0; j < n; j++){
            graph[i][j] = house[i][j];
        }
    }

    // 전부 순회
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(graph[i][j] == 1 && visited[i][j] == 0){
                result[index++] = BFS(graph, visited, n, i * n + j);
            }
        }
    }

    // 오름 차순 정렬 - 버블 정렬
    for(int i = 0; i < index - 1; i++){
        for(int j = 0; j < index - i - 1; j++){
            if(result[j] > result[j+1]){
                int temp = result[j];
                result[j] = result[j+1];
                result[j+1] = temp;
            }
        }
    }

    // 결과 출력
    for(int i = 0; i < index; i++){
        printf("%d ", result[i]);
    }
    printf("\n");

    // 메모리 해제
    for(int i = 0; i < n; i++){
        free(graph[i]);
        free(visited[i]);
    }

    free(graph);
    free(visited);
    free(result);

    return 0;
}

int BFS(int **graph, int **visited, int n, int start){
    
    // 단지 체크
    int count = 1;

    // 방향
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 큐
    Queue q;

    Queue_Init(&q, n * n);
    Enqueue(&q, start);
    
    // 좌표 구하기
    int x = start / n;
    int y = start % n;

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
            if(graph[nx][ny] == 0) continue;
            if(visited[nx][ny] == 1) continue;
            
            Enqueue(&q, nx * n + ny);
            visited[nx][ny] = 1; 
            count++;
        }
    }

    Queue_Terminate(&q);
    return count;

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

    q->front = q->rear = q->num = q-> max = 0;
}