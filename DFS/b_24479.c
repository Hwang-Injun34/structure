/*
[백준] 알고리즘 수업 - 깊이 우선 탐색 1
[문제]
오늘도 서준이는 깊이 우선 탐색(DFS) 수업 조교를 하고 있다. 
아빠가 수업한 내용을 학생들이 잘 이해했는지 문제를 통해서 확인해보자.

N개의 정점과 M개의 간선으로 구성된 무방향 그래프가 주어진다. 
정점 번호는 1번부터 N번이고 모든 간선의 가중치는 1이다.
정점 R에서 시작하여 우선 탐색으로 노드를 방문할 경우 노드의 방문 순서를 출력하자.


[입력]
N: 정점 수
M: 간선 
R: 시작 노드

5 5 1
1 4
1 2
2 3
2 4
3 4

[의사코드]
1. 아이디어
상태(v, visited[v])
(1) 시작 노드를 시작으로 
(2) DFS: for - graph[v][i] == 1 && visited[v] == 0 일 시에 해당 노드 출력 (반복)
(3) 모든 노드 순회 시 종료

2. 시간 복잡도
인접 행렬: O(N^2) 

*/
#include <stdio.h>
#include <stdlib.h>

int cnt = 1;

void DFS(int v, int **graph, int *visited, int *order, int n);

int main(int argc, char *argv[]){
    // 입력
    int n = 5;
    int m = 5;
    int start = 1;

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * (n+1));
    int *visited  = (int *)calloc(n+1, sizeof(int));
    int *order = (int *)calloc(n+1, sizeof(int));

    for(int i = 0; i <= n; i++){
        graph[i] = (int *)calloc(n+1, sizeof(int));
    }
    // 간선 입력
    graph[1][4] = graph[4][1] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[2][4] = graph[4][2] = 1;
    graph[3][4] = graph[4][3] = 1;

    DFS(start, graph, visited, order, n);

    printf("\n");
    for(int i = 0; i <= n; i++){
        printf("%d %d\n", i, order[i]);
    }

    // 메모리 해제
    for(int i = 1; i <= n; i++) free(graph[i]);
    free(graph);
    free(visited);
    free(order);

    return 0;
}

void DFS(int v, int **graph, int *visited, int *order, int n){
    visited[v] = 1;
    order[v] = cnt++;

    printf("%d ", v);
    fflush(stdout);
    for(int i = 1; i <= n; i++){
        if(graph[v][i] == 0) continue;
        if(visited[i]) continue;
        DFS(i, graph, visited, order, n);
    }
}