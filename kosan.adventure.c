#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

struct room{
	char name[9];
	char type[11];
	int cons;
	char connections[7][9];
};

void getRoomType(struct room* array, int i, FILE *file, int pos){
	char c;
	char type[11];
	int chars;

	fseek(file, pos, SEEK_SET);	//Sets file pos to where if left off
	fseek(file, 10, SEEK_CUR);	//Moves file position to room type

	memset(type, '\0', 11);

	chars = 0;
	do{
		c = fgetc(file);
		if(c != 10){
			type[chars] = c;
			chars++;
		}
	}while(c != 10);

	strcpy(array[i].type, type);
}

int getCons(struct room* array, int i, FILE *file){
	char c;
	char name[9];
	int chars, cons, index;

	fseek(file, 1, SEEK_CUR);
	cons = 0;
	do{
		memset(name, '\0', 9);	//Clears name string
		fseek(file, 13, SEEK_CUR);	//Start of connection name
		chars = 0;
		do{
			c = fgetc(file);
			if(c != 10){			//If next character is not newline
				name[chars] = c;
				chars++;
			}
		}while(c != 10);
		strcpy(array[i].connections[cons], name);
		c = fgetc(file);	//Checks first character of line
		cons++;
	}while(c != 82);		//If next character is not 'R'

	array[i].cons = cons;
	return ftell(file);
}

void getName(struct room* array, int i, FILE *file){
	char c;
	char name[9];
	memset(name, '\0', 9);
	int count;

	fseek(file, 11, SEEK_SET);	//Sets cursor to right at name

	count = 0;
	do{
		c = fgetc(file);
		if(c != 10){
			name[count] = c;
			count++;
		}
	}while(c != 10);

	strcpy(array[i].name, name);
}

void readFiles(char paths[7][33], struct room* array, int i){
	FILE *file = fopen(paths[i], "r");
	int filepos, j;
	// printf("path: %s\n", paths[i]);

	getName(array, i, file);
	// printf("filepos: %d\n", filepos);
	filepos = getCons(array, i, file);

	getRoomType(array, i, file, filepos);

	fclose(file);
}

void getPaths(char* dir, char names[7][33]){
	struct dirent *rdir_Struct;
	DIR *directory = opendir(dir);
	
	rdir_Struct = readdir(directory);
	rdir_Struct = readdir(directory);

	int i = 0;

	while(rdir_Struct = readdir(directory)){
		// printf("%s\n", rdir_Struct->d_name);
		strcpy(names[i], dir);
		strcat(names[i], "/");
		strcat(names[i], rdir_Struct->d_name);
		i++;
	}

	closedir(directory);
}

char* last_dir(){
	struct dirent *rdir_Struct;
	struct stat stat_Struct;
	DIR *directory = opendir(".");
	char* newest_dir = malloc(25 * sizeof(char));

	int largest = 0;
	int time;
	char name[25];

	/* The current directory, "." will always be last modified,
	 * so doing the command below will look at that directory
	 * first and basically start the rdir_Struct past the current
	 * directory. */
	rdir_Struct = readdir(directory);


	while(rdir_Struct = readdir(directory)){
		stat(rdir_Struct->d_name, &stat_Struct);
		int isDirectory = S_ISDIR(stat_Struct.st_mode);

		if(isDirectory){
			strcpy(name, rdir_Struct->d_name);
			time = stat_Struct.st_mtime;

			if(time > largest){
				largest = stat_Struct.st_mtime;
				strcpy(newest_dir, rdir_Struct->d_name);
			}			
		}
	}

	closedir(directory);
	return newest_dir;
}

//////////////////////////////////////////////////////

int getNext(struct room* array, char* str){
	int i;
	for(i = 0; i < 7; i++){
		if(strcmp(array[i].name, str) == 0){
			return i;
		}
	}

}

int validConnection(struct room* array, int cur, char* str){
	int i;
	for(i = 0; i < array[cur].cons; i++){
		if(strcmp(array[cur].connections[i], str) == 0){
			return i;
		}
	}

	printf("\nHUH? I DIDN'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
	return -1;
}

void printCurrent(struct room* array, int cur){
	int i;
	printf("CURRENT LOCATION: %s\n", array[cur].name);
	printf("POSSIBLE CONNECTIONS: ");
	for(i = 0; i < array[cur].cons; i++){
		if(i == (array[cur].cons - 1)){
			printf("%s.\n", array[cur].connections[i]);
		}else{
			printf("%s, ", array[cur].connections[i]);
		}
	}
	printf("WHERE TO? >");
}

int getInput(struct room* array, int cur, char* str){
	int dest;
	do{
		printCurrent(array, cur);
		memset(str, '\0', 50);
		fgets(str, 50, stdin);
		str[strlen(str) - 1] = '\0';	//removes newline char
		dest = validConnection(array, cur, str);
	}while(dest == -1);

	return dest;
}

int getStartIndex(struct room* array){
	int i;
	for(i = 0; i < 7; i++){
		if(strcmp(array[i].type, "START_ROOM") == 0){
			return i;
		}
	}
	return 0;
}

void Game(struct room* array){
	int cur = getStartIndex(array);
	int dest;
	int count = 0;
	char *str = malloc(50 * sizeof(char));
	// do{
		dest = getInput(array, cur, str);
		dest = getNext(array, str);
		count++;
		printf("goto: %s\n", array[dest].name);
	// }while()

	free(str);
}

int main(){
	int i, j;

	struct room *array;
	array = (struct room*) malloc(7 * sizeof(struct room));

	char* directory = last_dir();
	// printf("name: %s\n", directory);

	char paths[7][33];
	getPaths(directory, paths);

	for(i = 0; i < 7; i++){
		readFiles(paths, array, i);
	}

	// for(i = 0; i < 7; i++){
	// 	printf("ROOM NAME: %s\n", array[i].name);
	// 	for(j = 0; j < array[i].cons; j++){
	// 		printf("CONNECTION %d: %s\n", j+1, array[i].connections[j]);
	// 	}
	// 	printf("ROOM TYPE: %s\n\n", array[i].type);
	// }

	Game(array);
	
	free(array);
	free(directory);

	return 0;
}
