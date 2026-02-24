// app02 - 팩토리얼 재귀방식
// result를 int로 하면 12!까지만 계산 가능
// unsigned long long으로 하면 20!까지 계산 가능 

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

unsigned long long factorial(int n);

int main(void) {
	int x;
	unsigned long long result = 0;

	while (1) {
		printf("정수 입력 > ");
		scanf("%d", &x);

		result = factorial(x);

		printf("%d! = %llu \n", x, factorial(x));
	}

	return 0;
}

// factorial
// 0!, 1! = 1
// n! = n x (n-1)!
unsigned long long factorial(int n) {
	if (n > 0) {	// n x (n - 1)!
		// return n * factorial(n - 1);	// int 일 경우
		return (unsigned long long)n * factorial(n - 1);	// 5 * factorial(4) -> 5 * 4 * factorial(3)...
	}
	else {	// 0!
		return 1;
	}
}