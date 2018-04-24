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

		int rusr = st.st_mode & S_IRUSR;
		int wusr = st.st_mode & S_IWUSR;
		int xusr = st.st_mode & S_IXUSR;
		int rgrp = st.st_mode & S_IRGRP;
		int wgrp = st.st_mode & S_IWGRP;
		int xgrp = st.st_mode & S_IXGRP;
		int roth = st.st_mode & S_IROTH;
		int woth = st.st_mode & S_IWOTH;
		int xoth = st.st_mode & S_IXOTH;

		printf("%i %i %i %i %i %i %i %i %i\n", rusr, wusr, xusr, rgrp, wgrp, xgrp, roth, woth, xoth);
	}
	else{
		printf("Usage: %s <dossier/fichier/lien>\n", argv[0]);
	}
	return 0;
}