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

struct room* create_rooms(char namearray[10][9]){
	int i, rnum;
	struct room* RP = malloc(sizeof(room));
	// printf("names:%s\n", namearray[2]);
		
	for(i = 0; i < 7; i++){
		do{
			rnum = rand() % 10;
		}while(namearray[rnum] == "NULL");
		
		// strcpy(array[i]->name, "namehere");
		// strcpy(namearray[rnum], "NULL");
	
		// strcpy(array[1]->name, "name");
		// printf("name: %s\n", array[0]->name);
		// array[0]->type = 1;
	}

	return RP;

	// printf("type: %d\n", array[0]->type);
}

int main()
{
	int i;
	char foldername[30];
	int p = getpid();
	sprintf(foldername, "kosan.rooms.%d", getpid());

	char namearray[10][9]={
		"Batcave",
		"Room 101",
		"Holodeck",
		"Narnia",
		"Hobbiton",
		"Tatooine",
		"The John",
		"McDolans",
		"Walmart",
		"Muh Room"
	};

	struct room *array;
	array = create_rooms(namearray);

	// strcpy(array[0].name, "yoyoyo");
	// create_rooms(&array, namearray);

	// for(i = 0; i < 7; i++){
	// 	printf("name: %s\n", array[i].name);
	// }


	// scanf("%s", str);

	// printf("entered: %s\n", str);

	

	printf("pid: %d\n", p);

	// mkdir(foldername, 0700);

	return 0;
}