#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int compte(int* in){

	close(in[1]);

	char c;
	
	if(!read(in[0], &c, sizeof(char))){
		return 0;
	}

	int out[2];

	pipe(out);

	pid_t pid = fork();

	switch(pid){

	case -1:
		printf("Erreur: Problème fork\n");
		return EXIT_FAILURE;
		break;

	case 0:
		close(in[0]);
		compte(out);
		return EXIT_SUCCESS;
		break;

	default:
		close(out[0]);
		char i;
		int nb = 0;
		while(read(in[0], &i, sizeof(char))){
			if(i == c){
				nb++;
			}
			else{
				write(out[1], &i, sizeof(char));
			}
		}
		close(in[0]);
		close(out[1]);
		printf("%c : %i  ", c, nb);
		wait(NULL);
		return EXIT_SUCCESS;
		break;
	}	
}

int main(int argc, char const *argv[])
{
	if(argc == 2){
		int fd = open(argv[1], O_RDONLY);

		if(fd < 0){
			printf("Erreur: Lecture du fichier impossible\n");
			return EXIT_FAILURE;
		}

		int in[2];

		if(pipe(in) < 0){
			printf("Erreur: Problème pipe\n");
			return EXIT_FAILURE;
		}

		pid_t pid = fork();

		switch(pid){

		case -1:
			printf("Erreur: Problème fork\n");
			return EXIT_FAILURE;
			break;

		case 0:
			compte(in);
			return EXIT_SUCCESS;
			break;

		default:
			close(in[0]);
			char c;
			while(read(fd, &c, sizeof(char))){
				write(in[1], &c, sizeof(char));
			}
			close(fd);
			close(in[1]);
			wait(NULL);
			return EXIT_SUCCESS;
			break;
		}		
	}
	else{
		printf("Erreur: %s <fichier>\n", argv[0]);
	}
	return 0;
}