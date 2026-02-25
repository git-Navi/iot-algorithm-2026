// 1부터 N까지 적힌 카드 중에 카드 1장이 남고 마지막 카드 번호를 출력한다. 
// 그리고 다음 조건을 반복한다.
// 1. 맨 위 카드 1장을 버린다.
// 2. 그 다음 맨 위 카드 1장을 맨 아래로 옮긴다.

// 입력을 받으면 결과가 출력되는 형태로.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX 1000	// 그냥 아무 값이나 넣음.

int main(void) {
	int N;
	int que[MAX];
	int front = 0;
	int rear = 0;

	printf("카드 몇 장? > ");
	scanf("%d", &N);

	// rear 이용.
	for (int i = 1; i <= N; i++) {
		que[rear++] = i;
	}

	// 카드 한 장 남을 때까지!
	while (rear - front > 1) {
		// 맨 위 카드 1장을 버리고?
		front++;

		// 맨 위 카드 1장을 맨 아래로 옮긴다!
		que[rear++] = que[front++];
	}

	printf("%d\n", que[front]);

	return 0;
}
