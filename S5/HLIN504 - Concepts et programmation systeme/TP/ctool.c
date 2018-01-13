#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

typedef struct dirent dirent;

int isDir(const char* path);

int prof(const char* path);

int main(int argc, char const *argv[])
{
	if(argc == 2){
		int p = prof(argv[1]);
		
		if(p == -1)
			printf("%s n'est pas un chemin correct !\n", argv[1]);
		else
			printf("La profondeur de %s est %i !\n", argv[1], p);
	}
	else{
		printf("ERREUR ARGUMENT !\n");
	}

	return 0;
}

int isDir(const char* path){
	struct stat st;
	if(stat(path, &st) == -1){
		printf("can't open entity\n");
		return -1;
	}
	return S_ISDIR(st.st_mode);
}

int prof(const char path[]){

	if(!isDir(path)){
		return 0;
	}
	else{
		DIR* dir = NULL;
		dirent* entite = NULL;

		dir = opendir(path);

		if(!dir){
			printf("Ouverture dossier impossible !");
			return -1;
		}

		int maxp = 1;
		char chemin[1024];

		while((entite = readdir(dir))){
			
			strcat(strcat(strcpy(chemin, path), "/"), entite->d_name);
			
			if(isDir(chemin) && strcmp(entite->d_name, ".") && strcmp(entite->d_name, "..")){
				printf("%s\n", chemin);
				int p = 1 + prof(chemin);
				
				if(p > maxp){
					maxp = p;
				}
			}
		}

		return maxp;

		closedir(dir);
	}
}