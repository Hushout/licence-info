#ifndef TENTEN_H
#define TENTEN_H

#include "window.h"
#include "grille.h"
#include "setdepiece.h"
#include "score.h"

class TenTen{

 private:

  SetDePiece _setDePiece;
  Grille _grille;
  Score _score;
  int _nbMove;
  std::string _nomJoueur;

  //Demmarre la boucle de jeu du 1010 (sans Ncurse) et renvoie le dernier input
  int run();
  
 public:
  
  TenTen();
  
  //Accesseur en lecture:
  SetDePiece getSetDePiece(){return _setDePiece;}
  Grille getGrille(){return _grille;}
  std::string getNomJoueur(){return _nomJoueur;}
  int getNbMove(){return _nbMove;}

  //Accesseur en ecriture:
  void setNomJoueur(const std::string S){ _nomJoueur = S;}

  //Demmarre le jeu de 1010 avec Ncurse (jouable)
  void play();

  //Execute le jeux avec les options passées en parametre
  void traiteOption(int argc,  char** argv);

  //Change la piece à placer grace au SetDePiece
  void selectPieceSuiv();
  
  //Charge aleatoirement le SetDePiece
  void resetSetDePiece(); 

  //Charge toutes les pieces du jeu à partir d'un fichier
  void loadConfig(const std::string fichier);

  //Verifie si la partie est fini
  bool isGameOver();

  //Sauvegarde le jeu dans un fichier
  void saveGame(std::string nomFichier);
  
  //Charge le jeu à partir d'un fichier
  //numGame sert si plus d'un jeu est sauvegardé
  //numGame = 0 charge le premier jeu sauvegardé
  void loadGame(std::string nomFichier, int numGame);

  //Charge l'action effectué au tour precedant (reviens en arriere)
  void loadMovePrec();

  //Affiche le score du joueur dans une fenetre
  void printPlayerScore(Window& W, int y);

  //Affiche le score du joueur et les meilleurs score dans une fenetre
  void printInfo(Window& W, int y);

  //Sauvegarde les scores dans le fichier score.txt par ordre decroissant 
  void saveScore(std::string nomFichier);
};

//Affiche en rouge le bord de la fenetre d'indice "num" {0, 1, 2}
void selectWin(Window& W1, Window& W2, Window& W3, int num);

//Affiche le SetDePiece
void printSetDePiece(Window& W1, Window& W2, Window& W3, SetDePiece& S, int taille = 2);

//Affiche les meilleurs score dans une fenetre
void printBestScores(Window& W, int y);

//Affiche GAME OVER dans la Grille
void printGameOver(Window& W, int taille = 1);

//Traite l'option prise en parametres
void LireOption(std::string);

//Convertie un entier en chaine de caractere
char* itoa(unsigned int n);

#endif
