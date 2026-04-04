/*
해시 테이블
- 키와 값ㅇ르 쌍으로 저장하여, 검색 속도를 평균 O(1)로 향상시키는 자료구조
- 장점:
    - 데이터 삽입, 삭제, 검색이 매우 빠름
- 단점: 
    해시 충돌 해결을 위한 추가적인 구현 필요

체이닝(Chaining)
    - 충돌 발생 시 해당 버킷에 연결 리스트로 데이터를 연결
오픈 어드레싱
    - 충돌 시 해시 테이블 내의 다른 비어 있는 공간을 찾아 저장

설계 방향:
- Chaining 방식(연결 리스트 기반 해시 테이블)

index
[0] -> NULL
[1] -> [node]->[node]
[2] -> NULL
[3] -> [node]
...

*/

#ifndef HASHTABLE_H
#define HASHTABLE_H 

#define TABLE_SIZE 10

typedef struct _NODE{
    int key;
    int value;
    struct _NODE *next;
} NODE;

typedef struct _HASHTABLE{
    NODE *table[TABLE_SIZE];
} HASHTABLE;

// 초기화
void InitTable(HASHTABLE *ht);

// 해시 함수
int HashFunc(int key);

// 삽입
void Insert(HASHTABLE *ht, int key, int value);

// 검색
void Search(HASHTABLE *ht, int key);

// 삭제
void Delete(HASHTABLE *ht, int key);

// 전체 출력
void PrintTable(HASHTABLE *ht);

// 전체 삭제
void ClearTable(HASHTABLE *ht);

// 더미 데이터
void DummyData(HASHTABLE *ht);

#endif 
