// app05 - 소수 (Prime number)
// 1000 이하의 소수 나열

#include <stdio.h>

int main(void) {
	unsigned long counter = 0;	// 나눗셈 횟수
	int prime_cnt = 0;

	for (int n = 2; n <= 1000; n++) {
		// int i 쓰면 지역 변수라서 이 코드 블럭이 끝나면 사라진다.
		int i;
		for (i = 2; i < n; i++) {
			counter++;

			if (n % i == 0) {	// n이 i로 나누어 떨어지면, 소수가 아님.
				break;
			}

		}
		if (n == i) {
			prime_cnt += 1;
			printf("%d\n", n);	// 소수값 출력
		}
	}
	printf("1~1000 사이 소수 갯수 : %u\n", prime_cnt);
	printf("나눗셈 실행 횟수 : %u\n", counter);

	return 0;
}