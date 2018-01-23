#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//----------------------------------------------------client--------------------------------------------------------------------------
int main(int argc , char**argv)
{
struct sockaddr_in ad;

   int descbrLoc=socket(PF_INET,SOCK_STREAM,0);
  if(descbrLoc== -1)
    {
      printf("erreur socket");
    }

  
  ad.sin_family=AF_INET;
  ad.sin_addr.s_addr=INADDR_ANY;
  ad.sin_port=htons((short)0);
  int res=bind(descbrLoc, (struct sockaddr*)&ad, sizeof(ad));
  if(res<0){
    printf("erreur au bind");
    }
  

  //caracteristiques du serveur
  struct sockaddr_in adDistante;
  adDistante.sin_family=AF_INET;
  adDistante.sin_addr.s_addr=inet_addr(argv[1]);
  adDistante.sin_port=htons((short)31469);
 
  char* getNomFichier = (char*) malloc(sizeof(char*)*200);

  //----------------------------------------saisie du nom du fichier par l'utilisateur

  int taille;
  char tampon;



  //----------------------connexion---------------------------------------------------------
  //struct sockaddr_in adlocale;
  //printf(" numero de port de la BR locale : %d\n ", getsockname(descbrLoc,(struct sockaddr_in*) adlocale,sizeof(adlocale)); 

  printf("demande de connexion\n");
  int retourConnect = connect(descbrLoc, (struct sockaddr*)&adDistante,sizeof(adDistante));
  if(retourConnect==-1){
    printf("veuillez nous excuser mais il y'a une erreur de connection patron\n");
      exit(1);
  }
  printf("connexion etablie\n");
  printf("veuillez indiquer un nom de fichier :");
  fgets(getNomFichier,200,stdin);

  //----------------Envoi du id de l'utilisateur-------------------------------
  int retourSend= send(descbrLoc,getNomFichier,sizeof(getNomFichier),0);
  if(retourSend==-1){
    printf("erreur lors de l'envoi");
    exit(1);
  }


  //-----------------------Reception de la reponse du serveur-----------------------------
  int retourReciev = recv(descbrLoc, &taille, sizeof(int),0);
  if(retourReciev==-1){
    printf("erreur lors de la reception du msg");
    exit(1);
  }else printf("la taille du fichier demandé est : %d\n",taille);

  if(taille!=0){
    
    int tailleRecue = 0;
    int descFic = open(getNomFichier,O_CREAT,0750);
    int retourOpen = open(getNomFichier,O_WRONLY);

    while(tailleRecue<taille){
      tailleRecue+=recv(descbrLoc, &tampon, sizeof(char),0);
      printf("tailleRecu : %d\n",tailleRecue);
      int retourEcriture = write(retourOpen, &tampon,sizeof(tampon));
      if(retourEcriture==-1){
	printf("erreur dans l'écriture du fichier\n");
      }
    }
    close(descFic);//on ferme le fichier

  }else if(taille==0){
    printf("Le fichier %s n'est pas disponnible sur le serveur", getNomFichier);
  } 

  close(descbrLoc);
  return 0;
}
  
