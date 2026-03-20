/*
[프로그래머스] 게임 맵 최단거리
[문제]
ROR 게임은 두 팀으로 나누어서 진행하며, 상대 팀 진영을 먼저 파괴하면 이기는 게임이다. 
따라서, 각 팀은 상대 팀 진영에 최대한 빨리 도착하는 것이 유리하다. 

지금부터 당신은 한 팀의 팀원이 되어 게임을 진행하려고 한다. 
다음은 5x5 크기의 맵에, 당신의 캐릭터가 (행:1, 열:1) 위치에 있고, 
상대 팀 진영은(행:5, 열: 5)위치에 있는 경우의 예시이다. 

위 그림에서 검은색 부분은 벽으로 막혀있고 갈 수 없는 길이며, 흰색 부분은 갈 수 있는 길이다. 
캐릭터가 움직일 때는 동, 서, 남, 북 방향으로 한 칸씩 이동하며, 게임 맵을 벗어난 길은 갈 수 없다. 

아래 예시는 캐리거탁 상대 팀 진영으로 가는 두 가지 방법을 나타내고 있다. 

- 첫 번째 방법은 11개의 칸을 지나서 상대 팀 진영에 도착했다. 
- 두 번째 방법은 15개의 칸을 지나서 상대 팀진영에 도착했다. 

위 예시에서는 첫 번째 방법보다 더 빠르게 상대팀 진영에 도착하는 방법은 없으므로, 이 방법이 상대 팀 진영으로 가는 가장 빠른 방법이다. 

만약 상대 팀이 자신의 팀 진영 주위에 벽을 세워두었다면 상대 팀 진영에 도착하지 
못할 수도 있다. 

예를 들어, 다음과 같은 경우에 당신의 캐릭터는 상대 진영에 도착할 수 없다. 

게임 맵의 상태 maps가 매개변수로 주어질 떄, 
캐릭터가 상대 팀 진영에 도착하기 위해서 지나가야 하는 칸의 개수의 최소값을 return하도록 solution 함수를 완성하자. 

단, 상대팀 진영에 도착할 수 없을 때는 -1을 return 하자.

[입력]
[[1,0,1,1,1],[1,0,1,0,1],[1,0,1,1,1],[1,1,1,0,1],[0,0,0,0,1]]

[의사코드]
status:
    x, y, graph[x][y] = 지나온 거리

transition:
    방향: x, y -> (nx, ny) 
        - graph[nx][ny] != 0 

end:
    (x, y) == (n-1, m-1)



end:
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

int BFS(int **graph, int n);
int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int x);
int Dequeue(Queue *q, int *x);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);

int main(int argc, char *argv[]){
    int n = 5;
    int game_map[5][5] = {
        {1,0,1,1,1},
        {1,0,1,0,1},
        {1,0,1,1,1},
        {1,1,1,0,1},
        {0,0,0,0,1}
    };

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    
    for(int i = 0; i < n; i++){
        graph[i] = (int *)malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++) {
            graph[i][j] = game_map[i][j];
        }
    }

    // BFS 
    int answer = BFS(graph, n);

    // 메모리 출력
    printf("%d\n", answer);

    // 메모리 해제
    for(int i = 0; i < n; i++) free(graph[i]);
    free(graph);

    return 0;
}

int BFS(int **graph, int n){
    // 방향
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    
    Queue q;

    Queue_Init(&q, n * n);
    Enqueue(&q, 0);

    while(!Queue_IsEmpty(&q)){
        int pos;
        Dequeue(&q, &pos);
        int x = pos / n;
        int y = pos % n;

        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(graph[nx][ny] != 1) continue;

            graph[nx][ny] = graph[x][y] + 1;
            Enqueue(&q, nx * n + ny);
        }
    }
    Queue_Terminate(&q);

    if(graph[n-1][n-1] == 0) return -1;
    return graph[n-1][n-1];

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
    if(q->front==q->max) q->front = 0;

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