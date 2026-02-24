// IntQueue 구현 파일

#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

int Initialize(IntQueue* qu, int max) {
	qu->num = qu->front = qu->rear = 0;	// num, front, rear 0 초기화
	if ((qu->que = calloc(max, sizeof(int))) == NULL) {	// 동적배열할당 오류면?
		qu->max = 0;
		return -1;
	}
	qu->max = max;
	return 0;
}
int Enque(IntQueue* qu, int x) {
	if (qu->num >= qu->max) {	// 큐 Full
		return -1;
	}
	else {
		qu->num++;	// 데이터가 한 건 증가
		qu->que[qu->rear] = x;	// 큐 마지막에 추가
		qu->rear++;	// rear 1 증가

		if (qu->rear == qu->max) {
			qu->rear = 0;	// 큐의 리어가 배열의 마지막까지 다 찼으면
		}

		return 0;
	}
}

int Deque(IntQueue* qu, int* x) {
	if (qu->num <= 0) {
		return -1;
	}
	else {
		qu->num--;	// 큐에서 데이터가 하나 빠짐.
		*x = qu->que[qu->front];
		qu->front++;

		if (qu->front == qu->max) {	// deque를 계속해서 배열 마지막까지 도달
			qu->front = 0;
		}

		return 0;
	}
}

int Peek(const IntQueue* qu, int* x) {
	if (qu->num <= 0) {
		return -1;
	}

	*x = qu->que[qu->front];
	return 0;
}

void Clear(IntQueue* qu) {
	qu->num = qu->front = qu->rear = 0;
}

int Capacity(const IntQueue* qu) {
	return qu->max;
}

int Size(const IntQueue* qu) {
	return qu->num;
}

int Terminate(IntQueue* qu) {
	if (qu->que != NULL) {
		free(qu->que);
	}
	qu->max = qu->num = qu->front = qu->rear = 0;
}

int IsEmpty(const IntQueue* qu) {
	return qu->num <= 0;
}

int InFull(const IntQueue* qu) {
	return qu->num >= qu->max;
}

void Print(const IntQueue* qu) {
	for (int i = 0; i < qu->num; i++) {
		// (qu->front + i) % qu ->max
		// rear가 front보다 작을 수 있음.
		printf("%d ", qu->que[(qu->front + i) % qu ->max]);
	}
	printf("\n");
}

int Search(const IntQueue* qu, int x) {
	for (int i = 0; i < qu->num; i++) {
		int idx = (qu->front + i) % qu->max;
		if (qu->que[idx] == x) {
			return idx;
		}
	}

	return -1;
}

