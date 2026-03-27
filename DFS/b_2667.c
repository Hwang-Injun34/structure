/*
[백준] 단지번호 붙이기
[문제]
그림과 같이 정사각형 모양의 지도가 있다. 
1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다. 
철수는 이 지도를 가지고 연결된 집의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 
여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 
대각선상에 집이 있는 경우는 연결된 것이 아니다. 
지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.

[입력]
N: 정사각형 한 변
7
0110100
0110101
1110101
0000111
0100000
0111110
0111000

[의사코드]
1. 아이디어
(1) 상태: (x, y) 위치 + 해당 위치 방문 여부(visited)
(2) for문을 통해 1인 노드를 넣음
(3) DFS를 반복할 때마다 count++하여 (2단계)에 반환
조건: visited[x][y] == 0, (x, y) -> nx, ny(4가지 방향)이 1인 경우
(4) 모든 그래프를 순회하면 종료
(5) 결과값을 오름차순으로 정렬하여 출력

2. 시간 복잡도
O(N^2)

3. 자료구조
DFS
*/

#include <stdio.h>
#include <stdlib.h>

int DFS(int i, int j, int **map, int **visited, int n);

int main(int arc, char *argv[]){
    // 입력
    int n = 7;
    int map[7][7] = {
        {0,1,1,0,1,0,0},
        {0,1,1,0,1,0,1},
        {1,1,1,0,1,0,1},
        {0,0,0,0,1,1,1},
        {0,1,0,0,0,0,0},
        {0,1,1,1,1,1,0},
        {0,1,1,1,0,0,0}
    };

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    int **visited = (int **)malloc(sizeof(int *) * n);

    for(int i = 0; i <n; i++){
        graph[i] = (int *)malloc(sizeof(int) * n);
        visited[i] = (int *)calloc(n, sizeof(int));
        for(int j = 0; j < n; j++){
            graph[i][j] = map[i][j];
        }
    }

    int index = 0;

    // 결과 저장 리스트
    int *result = (int *)malloc(sizeof(int) * (n * n / 2));

    // 모든 아파트 순회
    for(int i = 0; i < n; i++){
        for(int j = 0; j <n; j++){
            if(graph[i][j] == 0) continue;
            if(visited[i][j]) continue;
            result[index++] = DFS(i, j, graph, visited, n);
        }
    }

    // 오름차순: 버블 정렬
    for(int i = 0; i < index - 1; i++){
        for(int j = 0; j < index - 1 -i; j++){
            if(result[j] > result[j+1]){
                int temp = result[j];
                result[j] = result[j+1];
                result[j+1] = temp;
            }
        }
    }

    // 결과 출력 
    printf("%d\n", index);

    for(int i = 0; i < index; i++){
        printf("%d\n", result[i]);
    }


    // 메모리 해제
    for(int i = 0; i < n; i++) {
        free(graph[i]);
        free(visited[i]);
    }
    free(visited);
    free(graph);
    free(result);
    
    return 0;
}

int DFS(int x, int y, int **graph, int **visited, int n){
    // 방향
    /*
                    (1, 0)
    (0, -1)                         (0, 1)
                    (-1, 0)
    */
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};

    visited[x][y] = 1;
    int count = 1;

    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx < 0 || ny < 0 || nx >= n || ny >=n) continue;
        if(graph[nx][ny] == 0 || visited[nx][ny]) continue;
        count += DFS(nx, ny, graph, visited, n);
    }
    return count;
}