// IntStack.c 스택 자료구조 함수 구현파일

#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"

/* -- 스택 초기화 -- */
int Initialize(IntStack* st, int max) {
	st->ptr = 0;	// 스택을 비우고 시작한다.
	if ((st->stk = calloc(max, sizeof(int))) == NULL) {	// 동적 배열 생성 실패
		st->max = 0;
		return -1;	// 오류 리턴
	}
	st->max = max;
	return 0;	// 오류 없이 초기화
}

/* -- 스택 데이터 push(푸시) -- */
int Push(IntStack* st, int x) {
	if (st->ptr >= st->max) {
		return -1;	// 오류 리턴, 데이터 추가 불가능
	}

	st->stk[st->ptr] = x;	// 이전 값 다음에 스택에 데이터 추가
	st->ptr++;	// ptr을 1 증가시킨다.
	// 혹은 st->stk[st->ptr++] = x; 만 사용해도 됨.

	return 0;	// 오류 없이 실행 종료
}

/* -- 스택 데이터 pop(팝) -- */
int Pop(IntStack* st, int* x) {
	if (st->ptr <= 0) {
		return -1;	// 오류 리턴
	}

	st->ptr--;	// ptr을 1 감소시킨다.
	*x = st->stk[st->ptr];

	return 0;
}

/* -- 스택 데이터 마지막 데이터 peek(피크) -- */
int Peek(const IntStack* st, int* x) {
	if (st->ptr <= 0) {	// 스택이 비어있음.
		return -1;	// 오류 리턴
	}

	//st->ptr--;	// ptr을 1 감소시킨다.
	//*x = st->stk[st->ptr];

	*x = st->stk[st->ptr - 1];

	return 0;
}

/* -- 스택 비우기 -- */
void Clear(IntStack* st) {
	st->ptr = 0;	// 다음에 데이터 푸시할 위치를 0으로 바꾼다.
	// 포인터 배열사에 데이터는 남아있음.
}

/* -- 스택 최대용량 -- */
int Capacity(const IntStack* st) {
	return st->max;
}

/* -- 스택 데이터 개수 -- */
int Size(const IntStack* st) {
	return st->ptr;
}

/* -- 스택 빈 여부 확인 -- */
int IsEmpty(const IntStack* st) {
	return st->ptr <= 0;	// 1 true, 0 false
}

/* -- 스택 만실 여부 확인 -- */
int IsFull(const IntStack* st) {
	return st->ptr >= st->max;
}

/* -- 스택 검색 -- */
int Search(const IntStack* st, int x) {
	for (int i = st->ptr - 1; i >= 0; i--) {
		if (st->stk[i] == x) {
			return i;	// 값이 있는 인덱스 리턴
		}
	}

	return -1;	// 0 인덱스에도 데이터가 존재하므로.
}

/* -- 스택 모든 데이터 출력 -- */
int Print(const IntStack* st) {
	for (int i = 0; i < st->ptr; i++) {
		printf("%d > ", st->stk[i]);
	}
	printf("\n");
}

void Terminate(IntStack* st) {
	if (st->stk != NULL) {
		free(st->stk);	// 메모리 해제
	}
	st->max = st->ptr = 0;	// max, ptr 모두 0으로 해제
}

