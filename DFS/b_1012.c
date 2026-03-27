/*
[백준] 유기농 배추
[문제]
차세대 영농인 하나는 강원도 고랭지에서 유기농 배추를 재배하기로 하였다. 
농약을 쓰지 않고 배추를 재배하려면 배추를 해충으로부터 보호하는 것이 중요하기 때문에, 
한나는 해충 방지에 효과적인 배추흰지렁이를 구입하기로 결삼힌다. 

이 지렁이는 배추 근처에 서식하며 해충을 잡아 먹음으로써 배추를 보호한다. 
특히, 어떤 배추에 배추흰지렁이가 한 마리라도 살고 있으면 이 지렁이는 인접한 다른 배추로 이동할 수 있어, 
그 배추들 역시 해충으로부터 보호받을 수 있다.
한 배추의 상하좌우 네 방향에 다른 배추가 위치한 경우에 서로 인접해 있을 것이다.

한나가 배추를 잽재하는 땅은 고르지 못해서 배추를 군데군데 심어 놓았다.
배추들이 모여있는 곳에는 배추흰지렁이가 한 마리가 있으면 되므로 서로 인접해 있는 배추들이 몇 군데에
퍼져있는지 조사하면 총 몇 마리의 지렁이가 필요한지 알 수 있다.

에를 들어, 배추밭이 아래와 같이 구성되어 있으면 최소 5마리의 배추희닞렁이가 필요하다. 
0은 배추가 심어져 있지 않은 땅이고, 1은 배추가 심어져 있는 땅을 나타낸다.

[입력]
여기서는 한 가지의 테스트 경우만을 사용하겠다.

가로: M, 10 
세로: N, 8
심은 배추: K, 17

10 8 17
0 0
1 0
1 1
4 2
4 3
4 5
2 4
3 4
7 4
8 4
9 4
7 5
8 5
9 5
7 6
8 6
9 6

[의사코드]
1. 아이디어
2차원 배열로 생각
(1) 상태: (x, y)위치와 visited[x][y]로 정의

(2) for문을 통해 모든 배열을 순회
조건: graph[x][y] == 1 && visited[x][y] == 0 이라면 DFS 
조건에 충족할 시에 count++;

(3) DFS: (x, y) -> (nx, ny)로 4가지 방향
방향의 조건과 (2)의 조건이 충족할 시에 DFS

(4) 모든 배추밭 순회 시 반환 후 종료

2. 시간 복잡도
O(N * N) -> O(N^2): N개의 요소 각각에 다시 N번의 연산을 수행

3. 자료구조
DFS

*/

#include <stdio.h>
#include <stdlib.h>

void DFS(int y, int x, int **graph, int **visited, int n, int m);


/*
방향
arr[y][x]
x: 가로
y: 세로
        (-1, 0)
(0, -1)          (0, 1)
        (1, 0)
*/
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(int argc, char *argv[]){
    // 입력
    int n = 8;
    int m = 10;
    int k = 17;

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    int **visited = (int **)malloc(sizeof(int *) * n);

    for(int i = 0; i < n; i++){
        graph[i] = (int *)calloc(m, sizeof(int));
        visited[i] = (int *)calloc(m, sizeof(int));
    }
    
    // 배추
    graph[0][0] = graph[1][1] = 1;
    graph[0][1] = 1;
    graph[2][4] = 1;
    graph[3][4] = 1;
    graph[5][4] = 1;
    graph[4][2] = 1;
    graph[4][3] = 1;
    graph[4][7] = 1;
    graph[4][8] = 1;
    graph[4][9] = 1;
    graph[5][7] = 1;
    graph[5][8] = 1;
    graph[5][9] = 1;
    graph[6][9] = 1;
    graph[6][8] = 1;


    int count = 0; 

    // 전체 순회
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(graph[i][j] && !visited[i][j]){
                count++;
                DFS(i, j, graph, visited, n, m);
            }
        }
    }

    // 결과 출력
    printf("%d\n", count);

    // 메모리 해제
    for(int i = 0; i < n; i++){
        free(graph[i]);
        free(visited[i]);
    }
    free(graph);
    free(visited);
    
    return 0;
}

void DFS(int y, int x, int **graph, int **visited, int n, int m){
    visited[y][x] = 1;

    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
        if(!graph[ny][nx]) continue;
        if(visited[ny][nx]) continue;
        
        DFS(ny, nx, graph, visited, n, m);
    }
}

