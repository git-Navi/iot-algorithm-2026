// 재귀함수 문제
// 1 + 2 + 3 ... + n 값 출력
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int sum(int n) {
	if (n == 1) {
		return 1;
	}
	
	return n + sum(n - 1);
}

int main(void) {
	int N;	// 정수 N
	printf("정수 N 입력 > ");
	scanf("%d", &N);

	printf("%d\n", sum(N));

	return 0;
}