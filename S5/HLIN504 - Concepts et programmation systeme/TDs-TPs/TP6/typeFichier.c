#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if(argc == 2){
		struct stat st;
		stat(argv[1], &st);

		if((st.st_mode & S_IFMT) == S_IFREG){
			printf("fichier !\n");
		}
		else if((st.st_mode & S_IFMT) == S_IFDIR){
			printf("dossier !\n");
		}
		else{
			printf("autre !\n");
		}
	}
	else{
		printf("Usage: %s <dossier/fichier/lien>\n", argv[0]);
	}
	return 0;
}