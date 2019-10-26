#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

struct room{
	char name[9];
	char type[11];
	int cons;
	int connections[7];
};

void print_to_file(struct room *array, int i, FILE *file){
	fprintf(file, "ROOM NAME: %s\n", array[i].name);
	int connCount = 1;
	int j;

	for(j = 0; j < 7; j++){
		if(array[i].connections[j] == 1){
			fprintf(file, "CONNECTION %d: %s\n", connCount, array[j].name);
			connCount += 1;
		}
	}

	fprintf(file, "ROOM TYPE: %s\n", array[i].type);
}

void create_files(struct room *array, char *foldername){
	int i;
	for(i = 0; i < 7; i++){
		char filepath[30];
		strcpy(filepath, foldername);
		strcat(filepath, "/");
		strcat(filepath, array[i].name);
		strcat(filepath, "_room");

		FILE *file;
		file = fopen(filepath, "w+");

		if(file == NULL){
			printf("File could not be created\n");
			exit(1);
		}

		print_to_file(array, i, file);

		// fprintf(file, "%s", "test");

		fclose(file);
	}

}

void print_rooms(struct room *array){
	int i, j;

	for(i = 0; i < 7; i++){
		printf("ROOM NAME: %s\n", array[i].name);
		int connCount = 1;
		for(j = 0; j < 7; j++){
			if(array[i].connections[j] == 1){
				printf("CONNECTION %d: %s\n", connCount, array[j].name);
				connCount += 1;
			}
		}
		printf("ROOM TYPE: %s\n\n", array[i].type);
	}
}

void add_connection(struct room *array, int current){
	int RandCon;
	do{
		RandCon = rand() % 7;
	}while(RandCon == current || array[current].connections[RandCon] == 1);

	array[current].connections[RandCon] = 1;
	array[RandCon].connections[current] = 1;
	array[current].cons += 1;
	array[RandCon].cons += 1;

}

void make_graph(struct room *array, int current, int ConsToAdd){
	while(array[current].cons < ConsToAdd){
		add_connection(array, current);
	}
}

void create_rooms(struct room *array, char namearray[10][9]){
	int i, j, rnum;

	srand(time(NULL));
		
	for(i = 0; i < 7; i++){
		do{
			rnum = rand() % 10;
		}while(strcmp(namearray[rnum], "NULL") == 0);

		strcpy(array[i].name, namearray[rnum]);
		strcpy(namearray[rnum], "NULL");

		if(i == 0){
			strcpy(array[i].type, "START_ROOM");
		}else if(i == 6){
			strcpy(array[i].type, "END_ROOM");
		}else{
			strcpy(array[i].type, "MID_ROOM");
		}	

		for(j = 0; j < 7; j++){
			array[i].connections[j] = 0;
		}

		array[i].cons = 0;
	}	

	for (i = 0; i < 7; i++){
		rnum = rand() % 4 + 3;
		make_graph(array, i, rnum);
	}

}

int main()
{
	int i;
	char foldername[30] = "kosan.rooms.";
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

	print_rooms(array);

	// printf("pid: %d\n", p);

	mkdir(foldername, 0700);

	create_files(array, foldername);

	free(array);

	return 0;
}