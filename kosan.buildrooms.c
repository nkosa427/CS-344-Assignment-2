#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stats.h>

int main()
{
	printf("hello world\n");
	char str[100];

	scanf("%s", str);

	printf("entered: %s\n", str);

	return 0;
}