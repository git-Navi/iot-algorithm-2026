// IntStack.h 스택 자료구조 헤더파일

#ifndef __INTSTACK	// 이름 지정에 큰 의미X, 자기가 원하는 대로 할 것.
#define __INTSTACK

// 스택을 구현하는 구조체
typedef struct {
	int max;	// 스택 용량
	int ptr;	// 스택 포인터
	int* stk;	// 스택 첫 요소에 대한 포인터
}IntStack;

// 스택용 함수 선언

/* -- 스택 초기화 -- */
// return type int는 실행 후 성공여부를 돌려받기 위해서
// return -1 : 초기화 실패
// return 0  : 초기화 성공
int Initialize(IntStack* s, int max);

/* -- 스택 데이터 push(푸시) -- */
// return -1 : push 실패
// return 0  : push 성공
int Push(IntStack* st, int x);

/* -- 스택 데이터 pop(팝) -- */
// return -1 : pop 실패
// return 0  : pop 성공
// 팝 결과는 x로 돌려받는다.
int Pop(IntStack* st, int* x);

/* -- 스택 데이터 마지막 데이터 peek(피크) -- */
int Peek(const IntStack* st, int* x);

/* -- 스택 비우기 -- */
void Clear(IntStack* st);

/* -- 스택 최대용량 -- */
int Capacity(const IntStack* st);

/* -- 스택 데이터 개수 -- */
int Size(const IntStack* st);

/* -- 스택 빈 여부 확인 -- */
int IsEmpty(const IntStack* st);

/* -- 스택 만실 여부 확인 -- */
int IsFull(const IntStack* st);

/* -- 스택 검색 -- */
int Search(const IntStack* st, int x);

/* -- 스택 모든 데이터 출력 -- */
int Print(const IntStack* st);

/* -- 스택 종료 -- */
void Terminate(IntStack* st);

#endif