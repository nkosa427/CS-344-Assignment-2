#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct room{
	char name[9];
	char type[11];
	int cons;
	struct room *connections;
};

void add_connection(struct room *array, int i){
	printf("adding connection\n");
}

void make_graph(struct room *array, int i, int rnum){
	while(array[i].cons < rnum){
		add_connection(array, i);
		array[i].cons += 1;
	}
}

void create_rooms(struct room *array, char namearray[10][9]){
	int i, rnum;

	srand(time(NULL));
		
	for(i = 0; i < 7; i++){
		do{
			rnum = rand() % 10;
		}while(strcmp(namearray[rnum], "NULL") == 0);

		strcpy(array[i].name, namearray[rnum]);
		strcpy(namearray[rnum], "NULL");

		if(i == 0){
			strcpy(array[i].type, "END_ROOM");
		}else if(i == 6){
			strcpy(array[i].type, "START_ROOM");
		}else{
			strcpy(array[i].type, "MID_ROOM");
		}	

		array[i].cons = 0;
	}

	for (i = 0; i < 7; i++){
		rnum = rand() % 4 + 3;
		printf("cons to make: %d\n", rnum);

		make_graph(array, i, rnum);
	}

}

// void free_struct_array(struct room *array){
// 	int i;
// 	for(i = 0; i < 7; i++){
// 		free(array[i]);
// 	}
// }

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

	// for(i = 0; i < 7; i++){
	// 	printf("name: %s\tType: %s\n", array[i].name, array[i].type);
	// }


	// scanf("%s", str);

	// printf("entered: %s\n", str);

	

	printf("pid: %d\n", p);

	// mkdir(foldername, 0700);

	// free_struct_array(array);
	free(array);

	return 0;
}