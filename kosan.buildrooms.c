#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct room{
	char name[9];
	int type;
	int numconnections;
	struct room *connections;
};

void create_rooms(struct room *array, char namearray[10][9]){
	int i, rnum;

	srand(time(NULL));
		
	for(i = 0; i < 7; i++){
		do{
			rnum = rand() % 10;
		}while(strcmp(namearray[rnum], "NULL") == 0);
		
		strcpy(array[i].name, namearray[rnum]);
		strcpy(namearray[rnum], "NULL");
	}


}

int main()
{
	int i;
	char foldername[30];
	int p = getpid();
	sprintf(foldername, "kosan.rooms.%d", getpid());

	char namearray[10][9]={
		"Batcave",
		"OSU",
		"Holodeck",
		"Narnia",
		"Hobbiton",
		"Tatooine",
		"TheJohn",
		"McDolans",
		"Walmart",
		"MuhRoom"
	};

	struct room *array;
	array = (struct room*) malloc(7 * sizeof(struct room));

	create_rooms(array, namearray);

	for(i = 0; i < 7; i++){
		printf("name: %s\n", array[i].name);
	}


	// scanf("%s", str);

	// printf("entered: %s\n", str);

	

	printf("pid: %d\n", p);

	// mkdir(foldername, 0700);

	return 0;
}