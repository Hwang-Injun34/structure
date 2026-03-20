/*
[프로그래머스] 타겟 넘버
[문제]
n개의 음이 아닌 정수들이 있다. 
이 정수들을 순서를 바꾸지 않고 적절히 더하거나 빼서 타겟 넘버를 만들려고 한다. 

예를 들어, [1, 1, 1, 1, 1]로 숫자 3을 만들려면 다음 다섯 방법을 쓸 수 있다. 

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3

+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

사용할 수 있는 숫자가 담긴 배열 numbers, 타겟 넘버 target이 매개변수로 주어질 때 숫자를 적절히 더하고 빼서 타겟 넘버를 만드는 방법의 수를 return.

[입력]
[1, 1, 1, 1, 1]	3

[의사코드]
status:
    index, sum

transtion: 
    x를 -x, +x로 한 뒤 큐에 삽입

end:
    sum == target -> count++

[출력]
타겟 넘버를 만드는 방법의 수 return
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int count; // 지금까지 처리한 숫자 갯수
    int sum; // 합
} Node;

typedef struct{
    int max;
    int num;
    int front;
    int rear;
    Node *node;
}Queue;

int BFS(int *num, int n, int target);

int Queue_Init(Queue *q, int max);
int Enqueue(Queue *q, int index, int sum);
int Dequeue(Queue *q, Node *node);
int Queue_IsEmpty(const Queue *q);
void Queue_Terminate(Queue *q);

int main(int argc, char *argv[]){
    int target = 3;
    int num[5] = {1, 1, 1, 1, 1};

    int n = sizeof(num) / sizeof(num[0]);

    // BFS 
    int answer = BFS(num, n, target);

    // 출력
    printf("%d\n", answer);

    return 0;
}

int BFS(int *num, int n, int target){
    
    Queue q;

    int size =1;
    for(int i = 0; i < n; i++) size *=2;
    Queue_Init(&q, size);

    Enqueue(&q, 0, 0);
    int count = 0;

    while(!Queue_IsEmpty(&q)){
        Node cur;
        Dequeue(&q, &cur);

        if(cur.count == n){
            if(cur.sum == target) count++;
            continue;
        }

        Enqueue(&q, cur.count+1, cur.sum + num[cur.count]);
        Enqueue(&q, cur.count+1, cur.sum - num[cur.count]);
    }

    Queue_Terminate(&q);
    return count;

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

int Enqueue(Queue *q, int count, int sum){
    if(q->num >= q->max) return -1;
    
    Node temp = {count, sum};
    q->node[q->rear++] = temp;
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

