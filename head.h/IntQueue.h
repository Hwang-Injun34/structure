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
#ifndef __Int_Queue_h__
#define __Int_Queue_h__

typedef struct {
    int max;    // 큐의 최대 용량
    int num;    // 현재의 요소 개수
    int front;  // 큐의 맨 앞 요소 커서
    int rear;  // 큐의 맨 뒤 요소 커서
    int *que;   // 큐의 본체
}IntQueue;

int IntQueue_Init(IntQueue *q, int max);
int IntQueue_Enqueue(IntQueue *q, int x);
int IntQueue_Dequeue(IntQueue *q, int *x);
int IntQueue_Peek(const IntQueue *q, int *x);
void IntQueue_Clear(IntQueue *q);
int IntQueue_Capacity(const IntQueue *q);
int IntQueue_Size(const IntQueue *q);
int IntQueue_isEmpty(const IntQueue *q);
int IntQueue_isFull(const IntQueue *q);
int IntQueue_Search(const IntQueue *q, int x);
void IntQueue_Print(const IntQueue *q);
void IntQueue_Terminate(IntQueue *q);
#endif // __Int_Queue_h__
