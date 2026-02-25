// 학생의 이름, 점수 N명 주어짐. 변수 N 선언하면 되겠지? 
// 최고 점수 학생 이름, 점수 출력 
// 동점의 경우 먼저 나온 점수 결정
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX 100
#define LEN 100

int main(void) {
	int N;
	char name[MAX][LEN];
	int score[MAX];

	printf("몇 명? > ");
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%s %d", name[i], &score[i]);
	}

	int idx = 0;
	for (int i = 1; i < N; i++) {
		// if문, score 비교
		if (score[i] > score[idx]) {
			idx = i;
		}
	}

	printf("%s %d\n", name[idx], score[idx]);

	return 0;
}