#include "syscall.h"

int main() {
	int id;
	id = Exec("/hello");
	Write("hey!\n", 5, 1);
	Join(id);
	Write("hey!\n", 5, 1);
	Exit(0);
}