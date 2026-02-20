// 포인터 01

#include <stdio.h>

int main(void) {
	int a = 10;
	int* pa = &a;

	/*int* pa;
	pa = &a;	// 와 동일함. */
	printf("a의 값 : %d\n", a);
	printf("a의 주소 : %p\n", &a);
	//printf("a의 주소 : %u\n", &a);
	printf("pa의 값(저장된 주소) : %p\n", pa);
	printf("pa가 가리키는 값 : %d\n", *pa);

	return 0;
}

// pa는 주소 저장, 변수 a의 주소를 담을 수도 있고 다른 정수형 변수의 주소도 담을 수 있음.
// *pa는 그 주소에 있는 실제값 -> a의 변수 값
// 포인터는 `값을 직접 들고 다니는게 아니라! 위치를 들고 다닌다.`