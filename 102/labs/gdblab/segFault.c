/* segFault.c
	program with a segfault
	to be used with gdb
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *buf;

	buf = malloc(1<<30);

	fgets(buf, 1024, stdin);
	printf("%s\n\n", buf);

	return 0;
}
