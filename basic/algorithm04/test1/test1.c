#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// hello -> olleh
// push, pop

int main(void) {

	char s[MAX];
	char stack[MAX];
	char res[MAX];
	int top = -1;
	int i;

	printf("문자열 입력 > ");
	scanf("%s", s);

	// push
	for (i = 0; s[i] != '\0'; i++) {
		stack[++top] = s[i];
	}

	// pop
	i = 0;
	while (top >= 0) {
		res[i++] = stack[top--];
	}
	res[i] = '\0';

	printf("%s\n", res);

	return 0;
}