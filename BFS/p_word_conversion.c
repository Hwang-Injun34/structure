/*
[프로그래머스] 단어 변환
[문제]
두 개의 단어 begin, target과 단어의 집합 words가 있다. 
아래와 같은 규칙을 이용하여 begin에서 target으로 변환하는 가장 짧은 변환 과정을 찾으려고 한다. 

1. 한 번에 한 개의 알파벳만 바꿀 수 있다. 
2. words에 있는 단어로만 변환할 수 있다.

예를 들어 begin이 "hit", target가 "cog", words가 ["hot","dot","dog","lot","log","cog"]라면 "hit" -> "hot" -> "dot" -> "dog" -> "cog"와 같이 4단계를 거쳐 변환할 수 있다.

두 개의 단어 begin, target과 단어의 집합 words가 매개변수로 주어질 때, 최소 몇 단계의 과정을 거쳐 begin을 target으로 변환할 수 있는지 return하시오. 

제한 사항
- 각 단어는 알파벳 소문자로만 이루어져있다. 
- 각 단어의 길이는 3이상 10이하이며 모든 단어의 길이는 같다. 
- words에는 3개 이상 50개 이하의 단어가 있으며 중복되는 단어는 없다. 
- begin과 target은 같지 않다. 
- 변환할 수 없는 경우에는 0를 return 

[입력]
begin: "hit"	
target: "cog"	
words: ["hot", "dot", "dog", "lot", "log", "cog"]

[의사코드]
1. begin에서 시작
2. 한글자 다른 단어 찾기
3. BFS 
4. target 도달하기

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int index;
    int step;
} Node;

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    Node * node;
} Queue;



int isOneDiff(char *a, char *b);
int BFS(char *begin, char *target, char words[][11], int wordsSize);

int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, Node node);
int Dequeue(Queue *q, Node *node);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);

int main(int argc, char *argv[]){
    //입력
    char begin[] = "hit";
    char target[] = "cog";
    char words[][11] = {"hot","dot","dog","lot","log","cog"};

    
    int wordsSize = sizeof(words)/sizeof(words[0]);

    // BFS 불러오기
    int answer = BFS(begin, target, words, wordsSize);
    printf("%d\n", answer);

    return 0;
}



int BFS(char *begin, char *target, char words[][11], int wordsSize){
    //큐
    Queue q;
    Queue_Init(&q, wordsSize);

    int *visited = (int *)calloc(wordsSize, sizeof(int));

    for(int i = 0; i < wordsSize; i++){
        if(isOneDiff(begin, words[i])){
            Node insert = {i, 1};
            Enqueue(&q, insert);
            visited[i] = 1;
        }
    }

    while(!Queue_IsEmpty(&q)){
        Node cur;
        Dequeue(&q, &cur);

        // 타겟과 비교
        if(strcmp(words[cur.index], target) == 0){
            int answer = cur.step;
            free(visited);
            Queue_Terminate(&q);

            return answer;
        }

        // 다음 단어 삽입
        for(int i = 0; i < wordsSize; i++){
            if(!visited[i] && isOneDiff(words[cur.index], words[i])){
                
                Node insert = {i, cur.step + 1};
                Enqueue(&q, insert);
                visited[i] = 1;
            }
        }
    }

    free(visited);
    Queue_Terminate(&q);

    return 0;
}





int isOneDiff(char *a, char *b){
    int diff = 0;
    for(int i = 0; a[i] != '\0'; i++){
        if(a[i] != b[i]) diff++;
    }
    return diff == 1;
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