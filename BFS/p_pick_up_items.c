/*
[프로그래머스] 아이템 줍기
[문제]
다음과 같은 다각형 모양 지형에서 캐릭터가 아이템을 줍기 위해 이동하려 한다.

지형은 각 변이 x축, y축과 평행한 직사각형이 겹쳐진 형태로 표현하며, 캐릭터는 이 당각형의 둘레를 따라서 이동한다.
만약 직사각형을 겹친 후 다음과 같이 중앙에 빈 공간이 생기는 경우, 다각형의 가장 바깥쪽 테두리가 캐릭터의 이동 경로가 된다.

단, 서로 다른 두 직사각형의 x축 좌표 또는 y축 좌표가 같은 경우는 없다.
즉, 위 그림처럼 서로 다른 두 직사각형이 꼭짓점에서 만나거나, 변이 겹치는 경우 등은 없다.
다음 그림과 같이 지형이 2개 이상으로 분리된 경우도 없다.

한 직사각형이 다른 직사각형 안에 완전히 포함되는 경우 또한 없다.

지형을 나타내는 직사각형이 담긴 2차원 배열 rectangle, 초기 캐릭터의 위치 characterX, characterY, 
아이템의 위치 itemX, itemY가 solution 함수의 매개변수로 주어질 때, 캐릭터가 아이템을 줍기 위해 이동해야 하는 가장 짧은 거리를 return 하도록 작성하자.

제한 사항
- rectangle의 세로(행) 길이는 1이상 4이하
- rectangle의 원소는 각 직사각형의 [좌측 하단 x, 좌측 하단 y, 우측 상단 x, 우측 상단 y] 좌표 형태이다.
    - 직사각형을 나타내는 모든 좌표값은 1이상 50이하인 자연수이다.
    - 서로 다른 두 직사각형의 x축 좌표, 혹은 y축 좌표가 같은 경우는 없다.
    - 문제에 주어진 조건에 맞는 직사각형만 입력으로 주어진다.

- characterX, characterY는 1이상 50이하인 자연수이다.
    - 지형을 나타내는 다각형 테두리 위의 한 점이 주어진다.
- itemX, itemY는 1이상 50이하인 자연수이다.
    - 지형을 나타내는 다각형 테두리 위의 한 점이 주어진다.
- 캐릭터와 아이템의 처음 위치가 같은 경우는 없다.

[입력]
rectangle: [[1,1,7,4],[3,2,5,5],[4,3,6,9],[2,6,8,8]]
charcter X, character Y: 1, 3 
itemX, itemY: 7, 8

[의사코드]
1. 그래프 만들기
2. 큐에 어떤 값을 넣을것인가
    - 캐릭터의 위치, 이동 값
3. BFS
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
    int dist;
} Node;

typedef struct{
    int max;
    int num;
    int front;
    int rear;
    Node *node;
}Queue;

int BFS(int rectangle[][4], int rectangleSize, int characterX, int characterY, int itemX, int itemY);
int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, Node node);
int Dequeue(Queue *q, Node *node);
void Queue_Terminate(Queue *q);
int Queue_IsEmpty(const Queue *q);

int main(int argc, char *argv[]){
    // 입력
    int rectangle[][4] = {
        {1, 1, 7, 4},
        {3, 2, 5, 5},
        {4, 3, 6, 9},
        {2, 6, 8, 8}
    };
    
    int characterX = 1;
    int characterY = 3;

    int itemX = 7;
    int itemY = 8;

    // rectangle 크기 구하기
    int rectangleSize = sizeof(rectangle)/sizeof(rectangle[0]);

    // BFS
    int answer = BFS(rectangle, rectangleSize, characterX, characterY, itemX, itemY);

    // 출력
    printf("%d\n", answer);

    return 0;
}

int BFS(int rectangle[][4], int rectangleSize, int characterX, int characterY, int itemX, int itemY){
    // board, visited만들기
    int board[102][102] = {0};
    int visited[102][102] = {0};

    // 사각형 채우기
    for(int r = 0; r < rectangleSize; r++){
        int x1 = rectangle[r][0] * 2;
        int y1 = rectangle[r][1] * 2;
        int x2 = rectangle[r][2] * 2;
        int y2 = rectangle[r][3] * 2;

        for(int i = x1; i <= x2; i++){
            for(int j = y1; j <= y2; j++){
                if(board[i][j] == 0)
                    board[i][j] = 1;
            }
        }
    }
    
    // 사각형 비우기
    for(int r = 0; r < rectangleSize; r++){
        int x1 = rectangle[r][0] * 2;
        int y1 = rectangle[r][1] * 2;
        int x2 = rectangle[r][2] * 2;
        int y2 = rectangle[r][3] * 2;

        for(int i = x1+1; i < x2; i++){
            for(int j = y1+1; j < y2; j++){
                if(board[i][j] == 1)
                    board[i][j] = 0;
            }
        }
    }

    // 방향
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 시작, 끝
    int startX = characterX * 2;
    int startY = characterY * 2;

    int endX = itemX * 2;
    int endY = itemY * 2;
    
    // 큐
    Queue q;
    Queue_Init(&q, 10000);
    
    
    Enqueue(&q, (Node){startX, startY, 0});
    visited[startX][startY] = 1;

    while(!Queue_IsEmpty(&q)){
        Node cur;
        Dequeue(&q, &cur);

        if(cur.x == endX && cur.y == endY){
            int answer = cur.dist / 2;
            Queue_Terminate(&q);
            return answer;
        }

        for(int i = 0; i < 4; i++){
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if(nx < 0 || ny < 0 || nx > 101 || ny > 101) continue;
            if(board[nx][ny] == 1 && !visited[nx][ny]){
                visited[nx][ny] = 1;
                Enqueue(&q, (Node){nx, ny, cur.dist + 1});
            }
        }
    }

    Queue_Terminate(&q);    
    return 0;

}

int Queue_Init(Queue *q, int max){
    q->front = q->rear = q->num = 0;
    q->node = (Node *)malloc(sizeof(Node) * max);

    if(q->node == NULL){
        q->max = 0;
        return -1;
    }

    q->max = max;
    return 0;
}

int Enqueue(Queue *q, Node node){
    if(q->num >= q->max) return -1;

    q->node[q->rear++] = node;
    if(q->rear == q->max) q->rear = 0;

    q->num++;
    return 0;
}

int Dequeue(Queue *q, Node *node){
    if(q->num <= 0) return -1;

    *node = q->node[q->front++];
    if(q->front == q->max) q->front = 0;

    q->num--;
    return 0;
}

int Queue_IsEmpty(const Queue *q){
    return q->num == 0;
}


void Queue_Terminate(Queue *q){
    if(q->node != NULL) free(q->node);

    q->front = q->rear = q->num = q->max = 0;
}
