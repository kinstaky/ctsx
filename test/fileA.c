#include "syscall.h"

int main() {
	int fileid;
	Create("/test1\0");
	fileid = Open("/test1\0");
	Write("hello\n", 6, fileid);
	Close(fileid);
	Exit(1);
}