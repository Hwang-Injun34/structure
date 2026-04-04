/*
[백준] ABCDE 
[문제]
BOJ 알고리즘 캠프에는 총 N명이 참가하고 있다. 
사람들은 0번부터 N-1번으로 번호가 매겨져 있고, 일부 사람들은 친구이다. 

오늘은 다음과 같은 친구 관계를 가진 사람 A, B, C, D, E가 존재하는지 구해보려고 한다. 

- A는 B와 친구이다. 
- B는 C와 친구이다. 
- C는 D와 친구이다. 
- D는 E와 친구이다. 

위와 같은 친구 관계가 존재하는지 안하는지 구하는 프로그램을 작성하시오.

[입력]
N: 사람 수
M: 친구 관계 수

5 4
0 1
1 2
2 3
3 4

[의사 코드]
1. 아이디어
(1) 상태: (N), visited[N]
(2) 시작 상태로부터 DFS를 통해 다음 노드를 방문 
조건: visited[N] == 0
(3) DFS + 백트레킹으로 깊이 체크

2. 시간 복잡도
O(N)

*/
#include <stdio.h>
#include <stdlib.h>

void DFS(int node, int depth, int **graph, int *visited, int n);
int found = 0;

int main(int argc, char *argv[]){
    // 입력
    int n = 5;
    int r = 4; 
    
    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * n);
    int *visited = (int *)calloc(n, sizeof(int));

    for(int i = 0; i < n; i++){
        graph[i] = (int *)calloc(n, sizeof(int));
    }
    // 연결 
    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[3][4] = graph[4][3] = 1;

    // DFS
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            DFS(i, 1, graph, visited, n);
            if(found) break;
        }
    }

    printf("%d\n", found);

    // 메모리 해제
    for(int i = 0; i < n; i++) free(graph[i]);
    free(visited);
    
    return 0;
}

void DFS(int node, int depth, int **graph, int *visited, int n){
    if(depth == n){
        found = 1;
        return;
    }
    
    visited[node] = 1;
    
    for(int i = 0; i < n; i++){
        if(visited[i]) continue;
        if(!graph[node][i]) continue;
        
        DFS(i, depth+1, graph, visited, n);
        if(found) return;
    }

    visited[node] = 0;
}