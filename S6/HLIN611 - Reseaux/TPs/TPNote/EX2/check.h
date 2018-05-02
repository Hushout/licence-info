#ifndef CHECK_H
#define CHECK_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define CHECK_ACTION exit

/* Les macros commençant par CHECK permettent de verifier si des erreurs sont presentent dans le programme. */

/* Verifie si l'allocation d'un descripteur de fichier s'est bien passée, affiche l'erreur et quitte le programme si ce n'est pas le cas. */
#define CHECK_FD(FD) 								\
if(FD < 0){											\
	fprintf(stderr, "Error : %s\n", strerror(FD));	\
	CHECK_ACTION(FD);										\
}													\

/* Verifie si l'allocation d'un fichier s'est bien passée, affiche l'erreur et quitte le programme si ce n'est pas le cas. */
#define CHECK_FILE(F, FNAME) 													\
if(F == NULL){																	\
	fprintf(stderr, "Error : Problème à l'ouverture du fichier %s\n", FNAME);	\
	CHECK_ACTION(1); 																	\
}																				\

/* Verifie si le numero passé en paramètre correspond à une erreur, affiche l'erreur et quitte le programme si ce n'est pas le cas. */
#define CHECK_ERROR(ERROR) 								\
if(ERROR < 0){											\
	fprintf(stderr, "Error : %s\n", strerror(ERROR));	\
	CHECK_ACTION(ERROR);								\
}														\

/* Verifie si les infos renvoyées par la fonction getaddrinfo sont valide, affiche l'erreur et quitte le programme si ça n'est pas le cas. */
#define CHECK_GAI_ERROR(ERROR) 									\
if(ERROR){														\
	fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(ERROR));	\
	CHECK_ACTION(ERROR);												\
}																\




#define CHECK_FD_R(FD, RETURN) 						\
if(FD < 0){											\
	fprintf(stderr, "Erreur : %s\n", strerror(FD));	\
	return RETURN;									\
}													\

#define CHECK_FILE_R(F, FNAME, RETURN) 											\
if(F == NULL){																	\
	fprintf(stderr, "Erreur : Problème à l'ouverture du fichier %s\n", FNAME);	\
	return RETURN;																\
}																				\

#define CHECK_ERROR_R(ERRNO, RETURN) 					\
if(ERRNO < 0){											\
	fprintf(stderr, "Erreur : %s\n", strerror(ERRNO));	\
	return RETURN;										\
}														\

#define CHECK_GAI_ERROR_R(ERRNO, RETURN) 						\
if(ERRNO){														\
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ERRNO));	\
	return RETURN;												\
}																\


#define CHECK_GAI(RESULT, ACTION) 													\
{																					\
	int check_error;																\
	if((check_error = (RESULT))){													\
		fprintf(stderr, "Getaddrinfo : %s\n", gai_strerror(check_error));			\
		ACTION;																		\
	}																				\
}																					\

#define CHECK(RESULT, ACTION) 														\
errno = 0;																			\
{																					\
	int check_error;																\
	if((check_error = (RESULT)) < 0){												\
		fprintf(stderr, "Error : %s\n", strerror(errno ? errno : check_error));		\
		ACTION;																		\
	}																				\
}																					\

#endif