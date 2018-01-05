#include "tenten.h"
#include <ctime>

TenTen::TenTen() : _setDePiece("piece.txt"), _grille(10, 10), _nbMove(0), _nomJoueur("[Name]"){
  _grille.setPiece(_setDePiece.getPiece());
}

int TenTen::run(){
  //initialisation de tout les parametres
  int ch;  
  int lignes = 10; 
  int colonnes = 10;
  Window WinMenu(lignes*4, (colonnes*8)/2, 0, 0, ' ');
  Window Win(lignes*4, colonnes*8, 42, 0, ' ');
  Window WinPiece1(12, (colonnes*8)/2, 124, 0, ' ');
  Window WinPiece2(12, (colonnes*8)/2, 124, 14, ' ');
  Window WinPiece3(12, (colonnes*8)/2, 124, 28, ' ');
  
  WinMenu.setCouleurBordure(BWHITE);
  WinMenu.setCouleurFenetre(WBLACK);
  Win.setCouleurBordure(BWHITE);
  Win.setCouleurFenetre(WBLACK);

  printGrille(Win, _grille);
  printSetDePiece(WinPiece1, WinPiece2, WinPiece3, _setDePiece);
  printInfo(WinMenu, 2);

  saveGame("gameMove.txt");

  //Lance la boucle de jeu
  while((ch = getch()) != 'q' && !isGameOver()){
    
   
    if(!_grille.pieceFit()){//Verifie si la piece sort de la grille
      _grille.makePieceFit();//Replace la piece dans la grille
      printGrille(Win, _grille);
    }
    switch (ch) {
    case 'c':
      Win.clear();
      break;
      
    case KEY_UP://Bouge la piece vers le haut
      _grille.movePiece(0, -1);
      printGrille(Win, _grille);
      break;
     
    case KEY_DOWN://Bouge la piece vers le bas
      _grille.movePiece(0, 1);
      printGrille(Win, _grille);
      break;
     
    case KEY_LEFT://Bouge la piece vers la gauche
      _grille.movePiece(-1, 0);
      printGrille(Win, _grille);
      break;
      
    case KEY_RIGHT://Bouge la piece vers la droite
      _grille.movePiece(1, 0);
      printGrille(Win, _grille);
      break;
      
    case 'a'://Permet de retourner en arriere dans les actions
      loadMovePrec();
      printSetDePiece(WinPiece1, WinPiece2, WinPiece3, _setDePiece);
      printGrille(Win, _grille);
      printInfo(WinMenu, 2);
      break;
      
    case '\t'://Permet de selectionner une autre piece
      selectPieceSuiv();
      printSetDePiece(WinPiece1, WinPiece2, WinPiece3, _setDePiece);
      printGrille(Win, _grille);
      break;
      
    case '\n'://Place la piece selectionnée dans la grille
      
      if(_grille.canPlacePiece()){//verifie si le placement est possible
	_grille.placePiece();//place la piece
	_score.Actualisation(_grille);
	
	//marque la piece comme placée dans le setDePiece
	_setDePiece.markAsPlaced(_setDePiece.getIndicePiece());

	if(_setDePiece.toutePiecePlace()){//verifie si toutes pieces placées
	  resetSetDePiece();//charge un setDePiece Aleatoire
	}
	else{
	  selectPieceSuiv();//change de piece
	}
	_nbMove++;//Incremente le nombre d'actions effectuées
	saveGame("gameMove.txt");//Sauvegarde l'action effectuée
	printSetDePiece(WinPiece1, WinPiece2, WinPiece3, _setDePiece);
	printGrille(Win, _grille);
	printInfo(WinMenu, 2);
      }
      break;
    }
  }
  if(ch != 'q'){
    //Affiche le GAME OVER et permet de revenir en arriere
    int input = 0;
    printGameOver(Win, 1);
    Win.print(22, 5, "VOTRE SCORE A ETE SAUVEGARDEE !", WBLACK);
    Win.print(22, 6, "     (APPUYEZ SUR ENTRER)", WBLACK);
    while(input != '\n'){
      input = getch();
      if(input == 'a'){
	loadMovePrec();
	run();
	input ='\n';
      }
    }
    //Enregistre le score le fichier score
    saveScore("score.txt");
  }
  return ch;
}

void TenTen::play(){
  int ch = 0;
  std::string choix;
  std::string nom;
  std::string nomSave;

  //Menu de debut de parti
  
  std::cout << "1:Nouveau jeu" << std::endl;
  std::cout << "2:Charger jeu" << std::endl;
  while(choix != "1" && choix != "2"){
    std::cin >> choix;
    if(choix == "1"){
      std::cout << "Entrez votre nom: ";
      std::cin >> nom;
      if(nom != ""){
	setNomJoueur(nom);
      }
    }
    else if(choix == "2"){
      std::cout << "Entrez le nom de la sauvegarde: ";
      std::cin >> nomSave;
      std::ifstream fichier(nomSave.c_str());
      
      if(!fichier){
	std::cout << "Erreur : chargement impossible !" << std::endl;
	exit(EXIT_FAILURE);
      }
      else{
	std::cout << "Chargement reussi !" << std::endl;
	std::cout << "Appuyez sur Entrer pour jouer !" << std::endl;
	std::cin.ignore();
	std::cin.get();
	loadGame(nomSave, 0);
      }
    }
  }
  
  //Programme principal
  
  std::remove("gameMove.txt");
  system("resize -s 42 166");
  startProgramX();
  
  ch = run();
  
  stopProgramX();
  system("resize -s 0 0");
  //system("clear");
  std::remove("gameMove.txt");
  
  //Menu de fin de parti
  
  if(ch == 'q'){
    choix = "";
    std::cout << std::endl;
    std::cout << "Partie interrompu, voulez-vous sauvegardé ?" << std::endl;
    std::cout << "1:Sauvegarder & quitter" << std::endl;
    std::cout << "2:Quitter" << std::endl;
    while(choix != "1" && choix != "2"){
      std::cin >> choix;
      if(choix == "1"){
	std::cout << "Entrez le nom de votre sauvegarde: ";
	std::cin >> nomSave;
      
	std::remove(nomSave.c_str());
	saveGame(nomSave);
	std::cout << "Sauvegarde reussi !" << std::endl;
	std::cout << "Appuyez sur Entrer pour quitter !" << std::endl;
	std::cin.ignore();
	std::cin.get();
	std::cout << "Merci d'avoir joué :)" << std::endl;
      }
    }
  }
}

void TenTen::traiteOption(int argc,  char** argv){
  
  if(argc == 1){  
    play();
  }
  else {
    std::string opt;
    for (int i = 1; i<argc ; i++){
      std::cout<<std::endl;
      opt = argv[i];
      if(opt == "-f"){
	opt = argv[i+1];
	std::ifstream fich (opt.c_str());
	i++;
	if(fich.is_open()){
	  loadConfig(opt);
	  play();
	}
	else{
	  std::cerr<<"ERREUR: impossible d'ouvrir le fichier "<<opt<<std::endl;
	}
	fich.close();
      }
      else {
	LireOption(opt);
      }
    }
  }
}

void TenTen::selectPieceSuiv(){
  int posX = _grille.getPiece().X();
  int posY = _grille.getPiece().Y();
  _setDePiece.changePiece();
  _grille.setPiece(_setDePiece.getPiece());
  _grille.setPieceXY(posX, posY);
}

void TenTen::resetSetDePiece(){
  int posX = _grille.getPiece().X();
  int posY = _grille.getPiece().Y();
  _setDePiece.loadRand();
  _grille.setPiece(_setDePiece.getPiece());
  _grille.setPieceXY(posX, posY);
}

void TenTen::loadConfig(const std::string fichier){
  _setDePiece.setFichierPiece(fichier);
  _grille.setPiece(_setDePiece.getPiece());
}

bool TenTen::isGameOver(){
  for(int i = 0 ; i < 3 ; i++){
    if(!_setDePiece.estPlace(i)){
      if(_setDePiece.at(i).aUnePlace(_grille)){
	return false;
      }
    }
  }
  return true;
}

void TenTen::saveGame(std::string nomFichier){
  std::ofstream os(nomFichier.c_str(), std::ios::app);

  if(!os){
    std::cout << "ERREUR: Dans saveGame, Impossible ouvrir fichier" << std::endl;
  }
  else{
    os << _score.getPoint() << " " << _nomJoueur << std::endl;
    os << "-" << std::endl;
    _setDePiece.saveSetDePiece(nomFichier);
    _grille.saveGrille(nomFichier);
    os.close();
  }
}

void TenTen::loadGame(std::string nomFichier, int numGame){
    std::ifstream fichier(nomFichier.c_str());

  if(!fichier){
    std::cout << "ERREUR: Dans loadGame, Impossible ouvrir fichier" << std::endl;
  }
  else{
    int point = 0;
    std::string nomJoueur;
    std::string ligne;
    fichier.seekg(posSeparateur(nomFichier, numGame*6) , std::ios::beg);
    getline(fichier, ligne);
    std::istringstream isstreamPointNom(ligne);
    isstreamPointNom >> point;
    isstreamPointNom >> nomJoueur;


    _nomJoueur = nomJoueur;
    _score.setPoint(point);

    
    _setDePiece.loadSetDePiece(nomFichier, numGame*6+1);
    _grille.loadGrille(nomFichier, numGame*6+4);
  }
}

void TenTen::loadMovePrec(){
  if(_nbMove > 0){
    TenTen T;
    //Charge l'avant dernier Mouvement enregistrer dans "gameMove.txt"
    _nbMove--;
    loadGame("gameMove.txt", _nbMove);
    
    //Enleve le dernier Mouvement enregistrer du fichier "gameMove.txt"
    for(int i = 0 ; i < _nbMove ; i++){
      T.loadGame("gameMove.txt", i);
      T.saveGame("gameMoveTemp.txt");
    }
    std::rename("gameMoveTemp.txt", "gameMove.txt");
  }
}

void TenTen::printPlayerScore(Window& W, int y){
  std::string actu = "SCORE ACTUEL:";
  std::string score = itoa(_score.getPoint());
  int X = W.getLargeur()/2 - ((actu.size()+1)/2);
  W.print(X, y, actu, WBLACK);
  X = W.getLargeur()/2 - (score.size()+1)/2;
  W.print(X, y + 2, score, WBLACK);
}

void TenTen::printInfo(Window& W, int y){
  W.clear();
  printPlayerScore(W, y);
  printBestScores(W, y + 5);
}

void TenTen::saveScore(std::string nomFichier){
  
  std::ofstream os(nomFichier.c_str(), std::ios::app);
  os.close();

  std::ifstream is(nomFichier.c_str());
  int posPlacement = 0;
  int scoreFichier = 0;
  bool estPlusPetit = true;
  int scoreJoueur = _score.getPoint();
  std::string scorePlusNom = itoa(scoreJoueur);
  scorePlusNom+= " "; scorePlusNom+= _nomJoueur;
  
  if(!is){
    std::cout<<"ERREUR :le fichier"<<std::endl;
  }
  else{

    std::string ligne;

    while(!is.eof() && estPlusPetit){
      posPlacement = is.tellg();
      getline(is,ligne);
      std::istringstream isstream2(ligne);
      isstream2 >> scoreFichier;
      if(scoreJoueur > scoreFichier){
	estPlusPetit = false;
      }
    }
  }
  is.close();
  
  std::string ligne;
  std::ifstream old(nomFichier.c_str());
  std::ofstream temp("temp.txt");
  bool estPlace = false;

  if(!old || !temp){
    std::cout<<"ERREUR : Dans saveScore, impossible ouvrir fichier"<<std::endl;
  }
  else{
    while(getline(old,ligne)){
      if(temp.tellp() == posPlacement){
	temp << scorePlusNom << std::endl;
	estPlace = true;
      }
      temp << ligne << std::endl;
    }
    if(!estPlace){
      temp << scorePlusNom << std::endl;
    }
  }
  old.close();
  std::rename("temp.txt",nomFichier.c_str());
  temp.close();
}

/////////

void selectWin(Window& W1, Window& W2, Window& W3, int num){
  if(num == 0){
    W1.setCouleurBordure(BRED);
    W2.setCouleurBordure(BWHITE);
    W3.setCouleurBordure(BWHITE);
  }
  if(num == 1){
    W1.setCouleurBordure(BWHITE);
    W2.setCouleurBordure(BRED);
    W3.setCouleurBordure(BWHITE);
  }
  if(num == 2){
    W1.setCouleurBordure(BWHITE);
    W2.setCouleurBordure(BWHITE);
    W3.setCouleurBordure(BRED);
  }
}

void printSetDePiece(Window& W1, Window& W2, Window& W3, SetDePiece& S, int taille){
  W1.clear();
  W2.clear();
  W3.clear();

  //affiche les pieces selon leurs formes
  int x = (W1.getLargeur()/4)/2 - (S.at(0).getLargeur()/2);
  int y = (W1.getHauteur()/2)/2 - (S.at(0).getHauteur()/2);

  printMat(W1, S.at(0), x, y, taille);

  x = (W2.getLargeur()/4)/2 - (S.at(1).getLargeur()/2);
  y = (W2.getHauteur()/2)/2 - (S.at(1).getHauteur()/2);
  
  printMat(W2, S.at(1), x, y, taille);

  x = (W3.getLargeur()/4)/2 - (S.at(2).getLargeur()/2);
  y = (W3.getHauteur()/2)/2 - (S.at(2).getHauteur()/2);

  printMat(W3, S.at(2), x, y,  taille);

  
  //Affiche le bord de la fenetre de la piece selectionnée en rouge
  selectWin(W1, W2, W3, S.getIndicePiece());
}

void printBestScores(Window& W, int y){
  std::ifstream is("score.txt");
  
  if(!is){
    std::cout<<"ERREUR : Dans printBestScores, impossible ouvrir fichier"<<std::endl;
  }
  else{
    int X = 0;
    std::string ligne;
    std::string score;
    std::string nom;
    std::string meilleur = "MEILLEURS SCORES:";
    
    X = W.getLargeur()/2 - ((meilleur.size()+1)/2);
    
    W.print(X, y, meilleur, WBLACK);
    
    for(int i = 0 ; i < 30 ; i+=2){
      getline(is,ligne);
      if(!is.eof()){
	std::istringstream isstream(ligne);
	isstream >> score;
	isstream >> nom;
	score += " ";
	std::string affiche = score + nom;
	X = W.getLargeur()/2 - ((affiche.size()+1)/2);
	W.print(X, y+2+i, affiche, WBLACK);
      }
    }
  }
}

void printGameOver(Window& W, int taille){
  Matrice M;
  M.load("gameOver.txt", 0);
  
  int x = 9;
  int y = 12;
  W.clear();
  printMat(W, M,x, y, taille);
}

void LireOption (std::string opt){
  if (opt == "-nom" || opt == "-name" || opt =="-n" ){ // Donne les noms. 
    std::cout<<"Thibault Odorico"<<std::endl;
    std::cout<<"Antoine Gouyon"<<std::endl;
    std::cout<<"Alexy Lefevre"<<std::endl;
    std::cout<<"Tristan Ramirez de Ribas"<<std::endl;
  }
  else if (opt == "-v" || opt == "-version"){ // Donne la version.
    std::cout<<"1.0"<<std::endl;
  }
  else if(opt == "-help" ){ // lit le fichier d'aide.
    std::ifstream Aide ("Aide.txt");
    if(Aide.is_open()){
      std::string ligne;
      while(getline(Aide,ligne)){
	std::cout<<ligne<<std::endl;
      }
    }
    else{
      std::cerr<<"ERREUR d'ouverture du fichier Aide.txt"<< std::endl;
    }
  }
  else{
    std::cerr<<"ERREUR l'option " << opt << " n'est pas valide."<<std::endl;
    std::cout<<" Tapez '-help' pour plus d'information."<<std::endl;
  }
}

char* itoa(unsigned int n){
  unsigned int k = n;
  int taille = 0;
  while(k != 0){
    k = k/10;   
    taille++;
  }
  char* T = new char[taille];
  for(int i = 0 ; i < taille ; i++){
    T[i] = 0;
  }
  sprintf(T, "%d", n);
  return T;
}
