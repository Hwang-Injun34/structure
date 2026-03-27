/*
[백준]DFS와 BFS
[문제]
그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오.(우리는 DFS)
단, 방문할 수 있는 정점이 여러 개인 경우에는 정점이 작은 것을 먼저 방문하고, 더 이상 방문할 수 있는 점이 없을 경우 종료한다. 
정점 번호는 1번부터 N번까지이다.

[입력]
N: 정점 수
M: 간선 수
시작 탐색 노드: 1
4 5 1
1 2
1 3
1 4
2 4
3 4

[의사코드]
1. 아이디어
(1) 시작 노드 1
(2) 상태 (v, visited[v] == 0)로 정의
(3) DFS: for문을 통해 (v, n_v) == 1 && visited[n_v] == 0이면 출력
(4) 모든 노드 순회시 종료

2. 시간복잡도
O(N^2)
인접 행렬을 사용하므로 각 노드마다 모든 노드를 확인해야 하여 O(N^2)
*/

#include <stdio.h>
#include <stdlib.h>

void DFS(int v, int **graph, int *visited, int n);

int main(int argc, char *argv[]){
    // 입력
    int n = 4;
    int e = 5;
    
    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * (n+1));
    int *visited = (int *)calloc(n+1, sizeof(int));

    for(int i = 0; i <= n; i++) {
        graph[i] = (int *)calloc(n+1, sizeof(int));
    }

    // 간선 연결
    graph[1][2] = graph[2][1] = 1;
    graph[1][3] = graph[3][1] = 1;
    graph[1][4] = graph[4][1] = 1;
    graph[2][4] = graph[4][2] = 1;
    graph[3][4] = graph[4][3] = 1;

    DFS(1, graph, visited, n);

    // 메모리 해제
    for(int i = 0; i <= n; i++) free(graph[i]);
    free(graph);
    free(visited);

    return 0;
}

void DFS(int v, int **graph, int *visited, int n){
    visited[v] = 1;
    printf("%d ", v);

    for(int i = 0; i <= n; i++){
        if(!graph[v][i]) continue;
        if(visited[i]) continue;
        DFS(i, graph, visited, n);
    }
}