// p52. 동적 할당
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int* x = malloc(sizeof(int));	// calloc(1, sizeof(int));
	if (x == NULL) {
		puts("메모리 할당 실패!");	// printf(); 사용 시에는 \n 사용해야함. 띄어쓰기 할 때.
		return 1;
	}

	*x = 57;
	printf("*x = %d\n", *x);

	free(x);

	// 배열 동적할당
	int na;
	printf("요소 개수 > ");
	scanf("%d", &na);

	int* ary = calloc(na, sizeof(int));	// malloc(sizeof(int) * na)
	if (ary == NULL) {
		puts("메모리 할당 실패!");
		return 1;
	}

	printf("%d개의 정수를 입력하세요.\n", na);
	for (int i = 0; i < na; i++) {
		printf("a[%d]", i);
		scanf("%d", &ary[i]);	// &ary[i]
	}

	printf("각 요소 값 출력 > \n");
	for (int i = 0; i < na; i++) {
		printf("a[%d] = %d\n", i, ary[i]);
	}

	free(ary);

	return 0;
}