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
	int connections[7];
};

void readFiles(char names[7][33], struct room* array){
	FILE *file = fopen(names[0], "r");
	char c;
	char name[9];
	int count;

	fseek(file, 11, SEEK_SET);	//Sets cursor to right at name

	count = 0;
	memset(name, '\0', 9);
	do{
		c = fgetc(file);
		if(c != 10){
			name[count] = c;
			count++;
		}
	}while(c != 10);

	printf("%s\n", name);

	if(strcmp(name, "OSU") == 0){
		printf("success\n");
	}

	// while(feof(file) == 0){
	// 	c = fgetc(file);
	// 	printf("%c", c);
	// 	if(c == 10){
	// 		printf("NEWLINE\n");
	// 	}
	// }
}

void getFileNames(char* dir, char names[7][33]){
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

			// printf("Name: %s\n", name);
			// printf("Time: %d\n", time);
			// printf("\n");

			if(time > largest){
				largest = stat_Struct.st_mtime;
				// strcpy(newest_dir, "/");
				strcpy(newest_dir, rdir_Struct->d_name);
			}			
		}
	}

	closedir(directory);
	return newest_dir;
}

int main(){

	// struct stat s;

	// // int is = stat(".", &s);
	// // printf("%d\n", is);
	// // printf("%d\n", s.st_mode);

	// struct dirent *d;
	// DIR *direc = opendir(".");

	// // while((d = readdir(direc)) != NULL){
	// // 	printf("%s\n", d->d_name);
	// // 	printf("%d\n", d->d_ino);
	// // 	printf("%c\n", d->d_type);
	// // 	printf("\n");
	// // }

	// while(d = readdir(direc)){
	// 	stat(d->d_name &s);
	// 	printf("%d\n", S_ISDIR(s.st_mode));
	// 	printf("%s\n", d->d_name);
	// 	printf("\n");
	// }

	// closedir(direc);

	struct room *array;
	array = (struct room*) malloc(7 * sizeof(struct room));

	char* directory = last_dir();
	printf("name: %s\n", directory);

	char paths[7][33];
	getFileNames(directory, paths);

	readFiles(paths, array);
	
	// int i;
	// for(i = 0; i < 7; i++){
	// 	printf("%s\n", names[i]);
	// }

	free(directory);

	return 0;
}
