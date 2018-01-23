#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

////////monserveur

 int compteurClient = 0;

void handler(int sig){
  compteurClient--;
}



int main(int argc, char ** argv)
{
  //_______________Creation Socketlocale_____________________
struct sockaddr_in ad;
 struct sigaction act;
 act.sa_handler=handler;
 sigaction(SIGCHLD, &act, NULL);

int descbrLoc=socket(PF_INET,SOCK_STREAM,0);
  if(descbrLoc== -1)
    {
      printf("erreur socket\n");
    }

 ad.sin_family=AF_INET;
 ad.sin_addr.s_addr=INADDR_ANY;
 ad.sin_port=htons((short)31469);
 int res=bind(descbrLoc, (struct sockaddr*)&ad, sizeof(ad));
 if(res<0){ printf("erreur au bind\n");}

 
 int retourFile=listen(descbrLoc,5);

 struct sockaddr_in BRCVClient;
 socklen_t lgBRCVClient=sizeof(BRCVClient);

 //----------acceptation ndes demandes en boucle, ensuite on fork---------------------------------

 while(1){
   if(compteurClient<6){
     int descBRCVServeur = accept(descbrLoc,(struct sockaddr*)&BRCVClient, &lgBRCVClient);   
     if(descBRCVServeur==-1){
       printf("erreur d'acceptation l'ami\n");
       exit(1);
     }
     compteurClient++;

   //-----affichage des informations concernant le client qui vient de se connecter-----------------
 
 /* Ces lignes provoquent pleins d erreurs, a ne surtout pas decommanter

    printf("l'adresse ip du client : %hhu\n",BRCVClient.sin_addr.s_addr);
    printf("le port du client est : %d\n",ntohs(BRCVClient.sin_port));
    printf("l'adresse ip du client : %hhu\n",inet_ntoa(BRCVClient.sin_addr));
 */
 //printf("adresse ip du client : %s \n", inet_ntoa(BRCVClient.sin_addr));
 // printf("adresse ip du client : %hhu \n",BRCVClient.sin_addr.s_addr[0]);
 // printf("numero de port du client : %d\n",ntohs(BRCVClient.sin_port)); 

     int retourFork=fork();

     if(retourFork==-1){

       printf("erreur du fork\n");

     }else if(retourFork>0){

       close(descBRCVServeur);

     }else if(retourFork==0){
    
       close(descbrLoc); 
       //afficher le nb de client en cours ;
       printf("%d clients en cours\n", compteurClient);
       int taille=0;
       char  msgRecu[200]="";
       char tampon;

       //-----------------reception d'un msg du client-----------------------------
       int retoureciev = recv(descBRCVServeur, &msgRecu, sizeof(msgRecu),0);
       if(retoureciev==-1){
	 printf("erreur lors de la reception du msg\n");
	 exit(1);
       }else printf(" le fichier demandé est : %s\n",msgRecu);
     

       /*-------------------------------ouverture du fichier demandé-------------*/
       int retourOpen = open(msgRecu,O_RDONLY);
       if(retourOpen==-1){
	 printf("erreur, le fichier n'existe pas");

       /*******-----------------si le fichier existe alors : ------------------------------*/
       }else{

	 //on parcourt le fichier pour connaitre sa taille
	 while(read(retourOpen, &tampon,1)!=0){
	   taille+=1;
	 }
	 printf("la taille du fichier %s est de %d\n",msgRecu,taille);
	 close(retourOpen);

       

	 //---------envoi la taille  au client---------------------------------------------------
	 int retourSend=send(descBRCVServeur, &taille, sizeof(int),0); 
	 if(retourSend==-1){
	   printf("erreur dans l'envoi de la taille au client\n");
	   exit(1);
	 }

	 /********************-----------------envoi du fichier---------------******/

	 //on a fermé le fichier et on le reouvre afin de replacer le pointeur au debut du fichier
	 retourOpen = open(msgRecu,O_RDONLY);
	 printf("1------------\n");
	 int tailleEnvoyee=0;
	 int retourLecture=1;
	 printf("2------------\n");
	 while(tailleEnvoyee<taille){

	   printf("3------------taille envoyee : %d , taille : %d\n",tailleEnvoyee, taille);
	   retourLecture = read(retourOpen, &tampon,1);
	   printf("4------------taille envoyee : %d , taille : %d\n",tailleEnvoyee, taille);

	   if(retourLecture==-1){
	     printf("erreur lors de la lecture du fichier");
	   }
	   printf("5------------taille envoyee : %d , taille : %d\n",tailleEnvoyee, taille);
	   tailleEnvoyee+=send(descBRCVServeur, &tampon, retourLecture,0);
	   printf("6------------taille envoyee : %d , taille : %d\n",tailleEnvoyee, taille);
	 }//fin d'envoi du fichier

       }
       //on ferme le fichier envoyé
       close(retourOpen);
       close(descBRCVServeur);
       kill(getppid(),SIGCHLD);
       printf("%d ---clients en cours apres fermeture du client\n",compteurClient);
       exit(0);
     }
     printf("%d clients en cours apres fermeture du client\n",compteurClient);
     close(descBRCVServeur); 

   }
 }
   return 0;
}
