/*
[백준] 연결 요소의 개수

[문제]
방향 없는 그래프가 주어졌을 때, 연결 요소의 개수를 구하는 프로그램을 작성하시외

[입력]
N: 정점 수
M: 간선 수
1 2
2 5
5 1
3 4
4 6

[의사코드]
1. 아이디어
(1) for - 모든 노드를 방문
조건: [node][node] == 1, vistied == 0
(2) DFS - 위 조건에 충족하면 계속 반복
(3) DFS 종료 시, 연결 요소 개수 + 1
(4) 모든 노드 순회 시 종료

2. 시간 복잡도
인접 리스트: O(V + E)
V: N
E: M 
O(N + M)

3. 자료구조 DFS
*/

#include <stdio.h>
#include <stdlib.h>

void DFS(int v, int **graph, int *visited, int n);

int main(int argc, char * argv[]){
    // 입력
    int n = 6; 
    int m = 5;

    int **graph = (int **)malloc(sizeof(int *) * n+1);
    int *visited = (int *)calloc(n+1, sizeof(int));
    for(int i = 0; i <= n; i++){
        graph[i] = (int *)calloc(n+1, sizeof(int));
    }

    // 간선입력
    graph[1][2] = graph[2][1] = 1;
    graph[2][5] = graph[5][2] = 1;
    graph[5][1] = graph[1][5] = 1;
    graph[3][4] = graph[4][3] = 1;
    graph[4][6] = graph[6][4] = 1;

    // 연결 요소 카운트
    int count = 0;

    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            DFS(i, graph, visited, n);
            count++;
        }
    }

    // 결과 출력
    printf("%d\n", count);

    // 메모리 해제
    for(int i = 0; i < n + 1; i++) free(graph[i]);
    free(graph);
    free(visited);
    return 0;
}

void DFS(int v, int **graph, int *visited, int n){
    visited[v] = 1;

    for(int i = 1; i <= n; i++){
        if(graph[v][i] == 1 && !visited[i]){
            DFS(i, graph, visited, n);
        }
    }
}