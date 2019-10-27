#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

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

			printf("Name: %s\n", name);
			printf("Time: %d\n", time);
			printf("\n");

			if(time > largest){
				largest = stat_Struct.st_mtime;
				strcpy(newest_dir, rdir_Struct->d_name);
				printf("largest: %s\n", newest_dir);
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

	char* directory = last_dir();
	printf("name: %s\n", directory);

	free(directory);

	return 0;
}
