// app02 - 버블 정렬

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*-- 버블 정렬 --*/
// n : 배열의 크기
void bubble_sort(int a[], int n);

/*-- 교환 함수 --*/
void swap(int* a, int* b);

int main(void) {
	int nx;

	puts("버블 정렬");
	printf("요소 개수 > ");
	scanf("%d", &nx);

	int* x = calloc(nx, sizeof(int));

	// 요소 개수만큼 입력
	for (int i = 0; i < nx; i++) {
		printf("x[%d] > ", i);
		scanf("%d", &x[i]);
	}

	bubble_sort(x, nx);

	puts("오름차순 정렬 완료!");
	for (int i = 0; i < nx; i++) {
		printf("x[%d] = %d ", i, x[i]);
	}

	free(x);

	return 0;
}

void bubble_sort(int a[], int n) {
	// 배열의 마지막 요소는 바깥쪽 for문에서 사용하지 않는다.
	for (int i = 0; i < n - 1; i++) {
		int exchg = 0;
		// 배열의 마지막 요소 전부터, 현재의 i 값까지 반복하면서 줄여든다.
		for (int j = n - 1; j > i; j--) {
			if (a[j - 1] > a[j]) {
				swap(&a[j - 1], &a[j]);
				exchg++;	// 교환 횟수, 값을 변경했다는 의미.
			}
		}

		if (exchg == 0) break;
	}
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}