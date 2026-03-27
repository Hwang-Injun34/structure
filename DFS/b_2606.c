/*
[백준] 바이러스
[문제]
신종 바이러스인 웜 바이러스는 네트워크를 통해 전파된다. 
한 컴퓨터가 웜 바이러스에 걸리면 그 컴퓨터와 네트워크 상에서 연결되어 있는 모든 컴퓨터는 웜 바이러스에 걸리게 된다. 

예를 들어 7대의 컴퓨터가 있다.
1번 컴퓨터가 웜 바이러스에 걸리면 웜 바이러스는 2번과 5번을 거쳐 
3번과 6번 컴퓨터까지 전파되어 2, 3, 6, 7 네 대의 컴퓨터는 웜바이러스에 걸리게 된다. 
하지만 4번과 7번 컴퓨터는 1번 컴퓨터와 네트워크 상에서 연결되어 있지 않기 때문에 영향을 받지 않는다.

어느날 1번 컴퓨터가 웜 바이러스에 걸렸다. 
컴퓨터의 수와 네트워크 상에서 서로 연결되어 있는 정보가 주어질 때
1번 컴퓨터를 통해 웜 바이러스에 걸리게 되는 컴퓨터의 수를 출력하는 프로그램을 작성하시오. 

[입력]
7
6
1 2
2 3
1 5
5 2
5 6
4 7

[의사코드]
1. 아이디어
시작: 노드 1
(1) 상태 n노드, visited[n] == 0 
(2) DFS: 현재 노드와 연결되어 있고 visited == 0인 경우에 카운트 증가
(3) 연결된 모든 노드 방문 시 종료

*/
#include <stdio.h>
#include <stdlib.h>

void DFS(int v, int **graph, int *visited, int n, int *count);

int main(int argc, char *argv[]){
    // 입력
    int n= 7;
    int m = 6;

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * (n+1));
    int *visited = (int *)calloc(n+1, sizeof(int));
    for(int i = 0; i <= n; i++) graph[i] = (int *)calloc(n+1, sizeof(int));

    // 간선 입력
    graph[1][2] = graph[2][1] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[1][5] = graph[5][1] = 1;
    graph[5][2] = graph[2][5] = 1;
    graph[5][6] = graph[6][5] = 1;
    graph[4][7] = graph[7][4] = 1;

    // 감염 컴퓨터 카운트
    int count = 0;

    DFS(1, graph, visited, n, &count);

    printf("%d\n", count);

    // 메모리 해제
    for(int i = 0; i <= n; i++) free(graph[i]);
    free(graph);
    free(visited);

    return 0;
}

void DFS(int v, int **graph, int *visited, int n, int *count){
    visited[v] = 1;

    for(int i = 1; i <= n; i++){
        if(graph[v][i] == 0) continue;
        if(visited[i]) continue;
        (*count)++;
        DFS(i, graph, visited, n, count);
    }
}