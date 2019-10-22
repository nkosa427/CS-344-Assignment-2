#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	printf("hello world\n");
	char str[100];

	scanf("%s", str);

	printf("entered: %s\n", str);

	getpid();

	return 0;
}