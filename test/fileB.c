#include "syscall.h"

int main() {
	char buffer[16];
	int file;

	Create("/test1");
	file = Open("/test1");
	Read((char*)buffer, 6, file);
	Write((char*)buffer, 6, 1);
	Close(file);
	Exit(1);
}