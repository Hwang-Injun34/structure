/*
[백준] 섬의 개수
[문제]
정사각형으로 이루어져 있는 섬과 바다 지도가 주어진다. 
섬의 개수를 세는 프로그램을 작성하시오.

한 정사각형과 가로, 세로 또는 대각선으로 연결되어 있는 사각형은 걸어갈 수 있는 사각형이다. 
두 정사각형이 같은 섬에 있으려면, 한 정사각형에서 다른 정사각형으로 걸어서 갈 수 있는 경로가 있어야 한다. 
지도는 바다로 둘러싸여 있으며, 지도밖으로 나갈 수 없다. 

[입력]
1: 땅, 0: 바다
4 3
1 0 1 0
0 1 0 0
1 0 1 1

[의사 코드]
1. 아이디어
(1) 상태: (y, x), visited[y][x]
(2) for문을 통해 좌표 전부 방문
DFS - graph[y][x] == 1, visited[y][x] 인 경우만
DFS가 종료될 때마다 
(3) 연결된 8방향 체크 하며 -> DFS로 반복

(4) 전부 다 방문했다면 섬의 개수 반환

2. 시간 복잡도
O(N * M)


*/

#include <stdio.h>
#include <stdlib.h>


void DFS(int **graph, int **visited, int n, int m, int y, int x);
// 8방향 생성 
/*
(-1, -1)    (-1, 0)     (-1, 1)
(0, -1)                 (0, 1)
(1, -1)     (1, 0)      (1, 1)
*/
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int main(int argc, char *argv[]){

    // 입력
    int n = 3;
    int m = 4;

    int map[3][4] = {
        {1, 0, 1, 0},
        {0, 1, 0, 0},
        {1, 0, 1, 1}
    };

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    int **visited = (int **)malloc(sizeof(int *)*n);

    for(int i = 0; i < n; i++){
        graph[i] = (int *)malloc(sizeof(int)*m);
        visited[i] = (int *)calloc(m, sizeof(int));
        for(int j = 0; j < m; j++){
            graph[i][j] = map[i][j];
        }
    }

    int answer = 0;

    // 전체 반복
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(graph[i][j] == 1 && visited[i][j] == 0){
                answer++;
                DFS(graph, visited, n, m, i, j);
            }
        }
    }

    // 결과 출력
    printf("%d\n", answer);

    // 메모리 해제
    for(int i = 0; i < n; i++){
        free(graph[i]);
        free(visited[i]);
    }
    free(graph);
    free(visited);

    return 0;
}

void DFS(int **graph, int **visited, int n, int m, int y, int x){
    visited[y][x] = 1;

    for(int i = 0; i < 8; i++){
        int ny = y + dy[i];
        int nx = x + dx[i]; 
        if(ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
        if(!graph[ny][nx]) continue;
        if(visited[ny][nx]) continue;
        DFS(graph, visited, n, m, ny, nx);
        
    }

}