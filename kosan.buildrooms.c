#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	char foldername[30];
	int p = getpid();
	sprintf(foldername, "kosan.rooms.%d", getpid());

	printf("%s\n", foldername);

	// scanf("%s", str);

	// printf("entered: %s\n", str);

	

	printf("pid: %d\n", p);

	mkdir(foldername, 0700);

	return 0;
}