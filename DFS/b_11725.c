/*
[백준] 트리의 부모 찾기
[문제]
루트 없는 트리가 주어진다.
이대, 트리의 루트를 1이라고 정했을 때, 각 노드의 부모를 구하는 프로그램을 작성하시오

[입력]
N: 노드 개수
1 6
6 3
3 5
4 1
2 4
4 7

2 - 4 - 1 - 6 - 3 - 5 
    |
    7

[출력]
1: x
2: 4
3: 6
4: 1
5: 3
6: 1
7: 4

[의사 코드]
1. 아이디어
모르는거:
노드와 간선이 주어졌을 때, 이것만으로 해당 노드의 부모 노드를 어떻게 구할 수 있는 것인가
-> 핵심 아이디어
1번에서 시작해서 내려가면서 "누가 나를 호출했는지"를 부모로 저장한다.(천재다)

(1) 상태: n, visited[n] == 0 -> 호출자를 저장해야하는데
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DFS(int v, int **graph, int *visited, int *parent, int n);

int main(int argc, char *argv[]){
    // 입력
    int n = 7;

    // 메모리 할당
    int **graph = (int **)malloc(sizeof(int *) * (n+1));
    int *visited = (int *)calloc(n+1, sizeof(int));
    int *parent = (int *)calloc(n+1, sizeof(int));
    
    for(int i = 0; i <= n; i++){
        graph[i] = (int *)calloc(n+1, sizeof(int));
    }

    // 간선 연결
    graph[1][6] = graph[6][1] = 1;
    graph[6][3] = graph[6][3] = 1;
    graph[3][5] = graph[3][5] = 1;
    graph[4][1] = graph[1][4] = 1;
    graph[2][4] = graph[4][2] = 1;
    graph[4][7] = graph[7][4] = 1;

    DFS(1, graph, visited, parent, n);

    // 출력
    for(int i = 2; i <= n; i++){
        printf("%d\n", parent[i]);
    }

    
    // 메모리 해제
    for(int i = 0; i <= n; i++){
        free(graph[i]);
    }
    free(graph);
    free(visited);
    free(parent);

    return 0;
}

void DFS(int v, int **graph, int *visited, int n){
    visited[v] = 1;

    for(int i = 1; i <= n; i++){
        if(graph[v][i] == 1 && !visited[i]){
            parent[i] = v;
            DFS(i, graph, visited, parent, n);
        }
    }
}