/**
 * 큐
 * - 선입선출
 * - enqueue: 데이터 삽입
 * - dequeue: 데이터 삭제
 * - rear: 데이터를 넣는 쪽
 * - front: 데이터를 꺼내는 쪽
 * 
 * 
 * 큐의 인터페이스
 * - IntQueue_Init: 큐의 초기화
 * - IntQueue_Enqueue: 데이터 삽입
 * - IntQueue_Dequeue: 데이터 삭제
 * - IntQueue_Peek: 맨 앞 데이터 참조
 * - IntQueue_Clear: 큐 비우기
 * - IntQueue_Capacity: 큐의 최대 용량
 * - IntQueue_Size: 큐에 쌓여 있는 데이터 개수
 * - IntQueue_isEmpty: 큐가 비었는가
 * - IntQueue_isFull: 큐가 가득 찼는가
 * - IntQueue_Search: 큐에서 데이터 검색
 * - IntQueue_Print: 큐의 모든 데이터 출력
 * - IntQueue_Terminate: 큐의 종료
*/
#ifndef Queue_H
#define Queue_H

typedef struct _QUEUE{
    int max;
    int num;
    int front;
    int rear;
    int *que;
} QUEUE;

// 큐 초기화
void Init(QUEUE *q, int max);

// 인큐
void Enqueue(QUEUE *q, int data);

// 디큐
void Dequeue(QUEUE *q, int *data);

// 전체 출력
void PrintAll(QUEUE *q);

// 비어있는지 체크
int IsEmpty(const QUEUE *q);

// 더미 데이터
void DummyData(QUEUE *q);

// 큐 종료
void Terminate(QUEUE *q);

#endif 
