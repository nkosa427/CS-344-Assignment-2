#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	printf("hello world\n");
	char str[100];

	// scanf("%s", str);

	// printf("entered: %s\n", str);

	int p = getpid();

	printf("pid: %d\n", p);

	return 0;
}