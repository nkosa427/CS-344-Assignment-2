#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>

pthread_mutex_t lock;
pthread_t thread;

struct room{
	char name[9];
	char type[11];
	int cons;
	char connections[7][9];
};

struct dynArray{
	int *arr;
	int size;
	int capacity;
};

void getRoomType(struct room* array, int i, FILE *file, int pos){
	char c;
	char type[11];
	int chars;

	fseek(file, pos, SEEK_SET);	//Sets file pos to where if left off
	fseek(file, 10, SEEK_CUR);	//Moves file position to room type

	memset(type, '\0', 11);		//clears this since it's used a lot

	chars = 0;
	do{
		c = fgetc(file);
		if(c != 10){						//if next char is newline
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
				chars++;				//Increments place in char array
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
	filepos = getCons(array, i, file);	//tracks position of stream cursor thing

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

void last_dir(char* newest_dir){
	struct dirent *rdir_Struct;
	struct stat stat_Struct;
	DIR *directory = opendir(".");
	// char* newest_dir = malloc(30 * sizeof(char));

	memset(newest_dir, '\0', 25);

	int largest = 0;
	int time;
	char name[24];

	/* The current directory, "." will always be last modified,
	 * so doing the command below will look at that directory
	 * first and basically start the rdir_Struct past the current
	 * directory. */
	rdir_Struct = readdir(directory);


	while(rdir_Struct = readdir(directory)){	//while stuff still in directory
		stat(rdir_Struct->d_name, &stat_Struct);	//gets stats
		int isDirectory = S_ISDIR(stat_Struct.st_mode);

		if(isDirectory){
			strcpy(name, rdir_Struct->d_name);	//gets name of directory
			time = stat_Struct.st_mtime;	//gets time modified

			if(time > largest){
				largest = stat_Struct.st_mtime;	//tracks latest modified folder
				strcpy(newest_dir, rdir_Struct->d_name);
			}			
		}
	}

	closedir(directory);
	// return newest_dir;
}

//////////////////////////////////////////////////////

void readTime(){
	char curTime[40];
	char c;
	int count = 0;
	memset(curTime, '\0', 40);

	FILE *file;
	file = fopen("currentTime.txt", "r");

	do{
		c = fgetc(file);
		if(c != 10){
			curTime[count] = c;
			count++;
		}		
	}while(c != 10);	//if next char not newline

	printf("\n%s\n", curTime);
	fclose(file);

}

void *writeTime(void *arg){
	pthread_mutex_lock(&lock);	//attempts lock. is run at very beginning of program
	time_t t;
	char str[50];
	struct tm *timeStruct;

	// char *directory = (char*)arg;

	// int file_descriptor = open(directory, O_WRONLY | O_CREAT, 5755);
	// printf("%s\n", directory);
	FILE *file;
	file = fopen("./currentTime.txt", "w+");

	t = time(NULL);
	timeStruct = localtime(&t);

	strftime(str, sizeof(str), "%I:%M%P, %A, %B %d, %Y", timeStruct);
	// int wr = write(file_descriptor, str, strlen(str) * sizeof(char));
	fprintf(file, "%s\n", str);
	fclose(file);

	pthread_mutex_unlock(&lock); //unlocks mutex

	return NULL;
}

//////////////////////////////////////////////////////

void resizeArray(struct dynArray *history){
	// printf("resizing\n");
	history->capacity = history->capacity * 2;
	int *newArr = malloc(history->capacity * sizeof(int));	//allocates more memory
	int i;
	for(i = 0; i < history->size; i++){
		newArr[i] = history->arr[i];	//copies stuff over
	}
	free(history->arr);		//frees memory from old array
	history->arr = newArr;	//points to new array
}

void addPath(struct dynArray *history, int cur, int count){
	// printf("size: %d\n", history->size);
	// printf("capacity: %d\n", history->capacity);

	if(history->size == history->capacity){		//checks if array needs to be bigger
		resizeArray(history);
	}
	history->arr[history->size] = cur;
	history->size += 1;
	// printf("added: %d\n", history->arr[history->size-1]);
}

int getNext(struct room* array, char* str){
	int i;
	for(i = 0; i < 7; i++){
		if(strcmp(array[i].name, str) == 0){		//gets index of next room
			return i;
		}
	}

}

int validConnection(struct room* array, int cur, char* str){
	int i;
	for(i = 0; i < array[cur].cons; i++){
		if(strcmp(array[cur].connections[i], str) == 0){		//checks if connection exists
			return i;
		}
	}

	printf("\nHUH? I DIDN'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
	return -1;
}

void printCurrent(struct room* array, int cur){
	int i;
	printf("\nCURRENT LOCATION: %s\n", array[cur].name);
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

void getInput(struct room* array, int cur, char* str, char* directory, pthread_t thread){
	int dest;
	do{
		printCurrent(array, cur);	//prints current room, prompt, etc.
		memset(str, '\0', 50);		//clears str since it's used a lot
		fgets(str, 50, stdin);		//reads user input
		str[strlen(str) - 1] = '\0';	//removes newline char
		if(strcmp(str, "time") == 0){
			pthread_mutex_unlock(&lock);	//Unlocks mutex to allow time function to run
			pthread_join(thread, NULL);		//waits for it to finish
			pthread_mutex_lock(&lock);		//Locks the mutex again
			pthread_create(&thread, NULL, writeTime, NULL);	//Creates thread again. repeat process.
			readTime(directory);		//this prints the current time from the file.
			dest = -1;	//to reprompt user for location.
		}else{
			dest = validConnection(array, cur, str);
		}
		
	}while(dest == -1);

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

void Game(struct room* array, char* directory, pthread_t thread){
	int cur = getStartIndex(array);		//cur is current room user is in
	int dest, i;
	int count = 0;
	char *str = malloc(50 * sizeof(char));
	
	struct dynArray *history;		//Made a dynamic array to store the user's path
	history = (struct dynArray*) malloc(sizeof(struct dynArray));
	history->arr = malloc(3 * sizeof(int));
	history->size = 0;
	history->capacity = 3;

	do{
		getInput(array, cur, str, directory, thread);
		cur = getNext(array, str);		//cur is place the user wants to go
		count++;
		addPath(history, cur, count);	//Adds next place to array
	}while(strcmp(array[cur].type, "END_ROOM") != 0);

	printf("CONGRATS! YOU'VE REACHED THE END!\n");
	printf("YOU TOOK %d STEPS.\n", count);
	printf("YOUR PATH THROUGH:\n");

	for(i = 0; i < history->size; i++){
		printf("%s\n", array[history->arr[i]].name);
	}

	free(str);
	free(history->arr);
	free(history);
}

int main(){
	int i, j;

	pthread_mutex_lock(&lock);					//Locks the mutex from the beginning
	pthread_create(&thread, NULL, writeTime, NULL);		//Creates the second thread which will try to also lock the mutex.

	struct room *array;		
	array = (struct room*) malloc(7 * sizeof(struct room));		//to recreate room struct from buildrooms program

	char* directory = malloc(100 * sizeof(char));		//holds path to recent directory
	last_dir(directory);

	char paths[7][33];
	getPaths(directory, paths);

	for(i = 0; i < 7; i++){
		readFiles(paths, array, i);
	}

	strcat(directory, "/currentTime.txt");	//Adds path for time function
	Game(array, directory, thread);
	// writeTime(directory);
	
	free(array);
	free(directory);
	pthread_mutex_destroy(&lock);

	return 0;
}
