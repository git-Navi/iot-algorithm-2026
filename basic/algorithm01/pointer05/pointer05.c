// app04 - 난수

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxof(const int* a, int n) {
	int max = a[0];
	for (int i = 0; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}

	return max;
}

int main(void) {
	int num;
	printf("사람 수 입력 > ");
	scanf("%d", &num);
	int* height = malloc(sizeof(int) * num);	// num 갯수만큼 동적 배열 할당
	srand(42);	// 난수를 만들때 필요한 시드(seed)값, 보통 42

	for (int i = 0; i < num; i++) {
		height[i] = 100 + rand() % 90;	// 100 ~ 189 사이 난수가 생성
		printf("height[%d] = %d\n", i, height[i]);
	}

	printf("가장 키가 큰 사람은 %d입니다.\n", maxof(height, num));

	free(height);

	return 0;
}