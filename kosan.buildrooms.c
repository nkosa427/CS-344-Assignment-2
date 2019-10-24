#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct room{
	char name[9];
	int type;
	int numconnections;
	struct room *connections;
};

void create_rooms(){

}

int main()
{
	char foldername[30];
	int p = getpid();
	sprintf(foldername, "kosan.rooms.%d", getpid());

	struct room *array;
	array = (struct room*) malloc(7 * sizeof(struct room));

	strcpy(array[0].name, "hello");
	printf("name: %s\n", array[0].name);


	// scanf("%s", str);

	// printf("entered: %s\n", str);

	

	printf("pid: %d\n", p);

	// mkdir(foldername, 0700);

	return 0;
}