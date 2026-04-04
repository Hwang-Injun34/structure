/*
중요 포인트
- Tail 관리
if(cur == list->tail)
    list->tail= prev;

- Empty 상태
list->head->next == NULL

- Dummy Head 덕분에
if(head == NULL) 하지 않아서 코드가 깔끔해진다. 
*/

#ifndef LIST_H 
#define LIST_H 

typedef struct _NODE{
    int data;
    struct _NODE *next;
} NODE;

typedef struct _LIST{
    NODE *head; 
    NODE *tail;
} LIST;


// 초기화
void InitList(LIST *list);

// 머리에 삽입
void InsertFront(LIST *list, int data);

// 꼬리에 삽입
void InsertRear(LIST *list, int data);

// 머리 노드 삭제
void RemoveFront(LIST *list);

// 꼬리 노드 삭제
void RemoveRear(LIST *list);

// 선택 노드 삭제
void RemoveByValue(LIST *list, int data);

// 모든 노드 삭제
void ClearList(LIST *list);

// 선택한 노드의 데이터 출력
void PrintNode(LIST *list, int data);

// 모든 노드 출력
void PrintAll(LIST *list);

// 연결 리스트 종료
void Terminate(LIST *list);

// 더미 데이터
void DummyDataFront(LIST *list);

void DummyDataRear(LIST *list);


#endif 
