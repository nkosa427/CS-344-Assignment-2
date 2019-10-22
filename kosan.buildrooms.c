#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	printf("hello world\n");
	char *folderstart = "kosan.rooms.";
	char strbuffer[40];
	char folername[70];
	int p = getpid();

	sprintf(strbuffer, "kosan.rooms.%d", p);

	printf("%s\n", strbuffer);

	// scanf("%s", str);

	// printf("entered: %s\n", str);

	

	printf("pid: %d\n", p);

	mkdir(strbuffer, 0700);

	return 0;
}