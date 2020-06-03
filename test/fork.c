#include "syscall.h"

void Hello() {
	int i;
	int j;
	int a;
	a = 0;
	for (i = 0; i != 3; ++i) {
		Write("Hello!\n", 7, 1);
		// for (j = 0; j != 100000; ++j) {
		// 	a += 1;
		// }
		Yield();
	}
	return;
}

int main() {
	int i;
	int j;
	int a;
	a = 0;
	Fork(Hello);
	for (i = 0; i != 3; ++i) {
		Write("Hey!\n", 5, 1);
		// for (j = 0; j != 100000; ++j) {
		// 	a += 1;
		// }
		Yield();
	}
	return 0;
}