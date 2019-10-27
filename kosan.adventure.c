#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void last_dir(){
	struct dirent *rStruct;
	struct stat sStruct;
	DIR *directory = opendir(".");

	while(rStruct = readdir(directory)){
		stat(rStruct->d_name, &sStruct);
		int isDirectory = S_ISDIR(sStruct.st_mode);

		if(isDirectory){
			printf("Name: %s\n", rStruct->d_name);
			printf("Time: %d\n", sStruct.st_mtime);
			printf("\n");
		}
	}

	closedir(directory);
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

	last_dir();

	return 0;
}
