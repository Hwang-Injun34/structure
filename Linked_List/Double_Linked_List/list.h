#ifndef LIST_H
#define LIST_H 

typedef struct _NODE{
    int data;
    struct _NODE *prev;
    struct _NODE *next;
} NODE;

typedef struct _LIST{
    NODE *head;
    NODE *tail;
} LIST;

// 초기화
void InitList(LIST *list);

// 삽입(맨 뒤)
void AddNode(LIST *list, int data);

// 머리 노드 삭제
void RemoveFront(LIST *list);

// 꼬리 노드 삭제
void RemoveRear(LIST *list);

// 선택 노드 삭제
void RemoveByValue(LIST *list, int data);

// 선택 노드 출력
void PrintNode(LIST *list, int data);

// 전체 출력
void PrintAll(LIST *list);

// 역방향 출력
void PrintReverse(LIST *list);

// 전체 삭제
void ClearList(LIST *list);

// 완전 종료
void Terminate(LIST *list);

// 더미 데이터
void DummyData(LIST *list);

#endif 
