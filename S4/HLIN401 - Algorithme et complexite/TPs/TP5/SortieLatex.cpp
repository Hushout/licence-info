//SortieLatex.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include "AB.h"

void SortieLatex(AB Ar, std::string filepath);

std::string* TikzRecursAB(int ligne,int gauche, int droite, int numeroPere, int typeFils, AB Ar);



std::string * TikzRecursAB(int ligne,int gauche, int droite, int numeroPere, int typeFils, AB Ar){
  std::ostringstream ossnum, osslign,osscol,ossnumPere, ossbal, ossnum2Pere,ossnumRac;

      std::string stres("");

      if (Ar) {
    ossnumPere<<numeroPere;
    ossnumRac<<"(\\textcolor{red}{" << Ar->racine << "})\\\\this=\\textcolor{red}{" <<Ar <<"}\\\\Pere=\\textcolor{red}{"<<Ar->Pere << "} (FGP=\\textcolor{red}{" << (Ar->FGP?"Gauche":"Droit") <<"})";

    if (Ar->Pere )ossnum2Pere<<Ar->Pere->racine; else ossnum2Pere<<0;

    int numero;
    if (typeFils==-1) { numero=1; } else { numero= 2*numeroPere + typeFils; }
    ossnum<<numero;
    osslign<<ligne;
    int mil = (gauche + droite)/2;

    osscol<<mil;

    stres="\\node[draw, color=black, rounded corners=5pt, text width=3cm, text centered] (SZ" + ossnum.str()    + ") at " +
	  "("   + osscol.str()    + ", " + osslign.str() + ") " + 
	  "{ "  + ossnumRac.str() + "};\n";

    if (typeFils!=-1) stres+="\\draw[->, >=latex, color=blue] (SZ"+ossnumPere.str()+") -- (SZ"+ossnum.str() +");\n";

    if (Ar->SAG) stres+=*TikzRecursAB(ligne-3,gauche,mil-13,numero,0,Ar->SAG);
    if (Ar->SAD) stres+=*TikzRecursAB(ligne-3,mil+13,droite,numero,1,Ar->SAD); 
 }
  return new std::string(stres);
}

std::string * TikzAB(AB Ar){
  return TikzRecursAB(1,1,10,1,-1,Ar);
}

 void SortieLatex(AB Ar, std::string filepath){ //don't insert garbage in filepath, its std::system-ised.
 std::ofstream fichier(filepath.c_str(), std::ios::out | std::ios::trunc);
 std::string preamb ("\\documentclass{article} \n \\usepackage{tikz} \n \\begin{document} \n \\resizebox{300pt}{!}{\n \\begin{tikzpicture}\n");
  std::cout<<preamb<<"\n";
std::string post("\\end{tikzpicture}\n } \\end{document} \n"); //rsz box end?
  std::cout<<post<<"\n";
 std::cout<<*TikzAB(Ar)<<"\n";
std::string   res1(preamb + *TikzAB(Ar));
 std::string   res(res1 + post);
 //std::cout<<res1<<"\n";
  fichier <<res<<"\n";
  fichier.close();

  std::ostringstream system_CARE;
  // /dev/null 2>&1 isnt enough to mute pdflatex...
  system_CARE << "mkdir pdflatex_temp > /dev/null 2>&1;" 
              << "pdflatex -output-directory=\"./pdflatex_temp\" -interaction=nonstopmode \"" << filepath << "\" >/dev/null 2>&1;"
	      << "mv ./pdflatex_temp/*.pdf ./ > /dev/null 2>&1;";
  std::system(system_CARE.str().c_str());
  return;
}


int main(int argc, char** argv){

  //Creation de L'Arbre de base (Rac)
  AB A0=new Sommet(0), A2=new Sommet(2), A4=new Sommet(4), Rac=new Sommet(6),
    A1= new Sommet(0), A3=new Sommet(2), A5=new Sommet(4);

  A0->GrefferSAD(A4);
  A0->GrefferSAG(A2);

  A1->GrefferSAD(A5);
  A1->GrefferSAG(A3);

  Rac->GrefferSAD(A0);
  Rac->GrefferSAG(A1);

  
  AB CopieRac = new Sommet(*Rac);
  
  if(argc == 2 && (atoi(argv[1]) >= 1 && atoi(argv[1]) <= 3)){
    //Supression du sous arbre droit de CopieRac
    if(atoi(argv[1]) == 1){
      CopieRac->SupprimerSAD();
      SortieLatex(CopieRac,"1 - Arbre (supprimerSAD)");
    }
    //Supression du sous arbre gauche de CopieRac
    if(atoi(argv[1]) == 2){
      CopieRac->SupprimerSAG();
      SortieLatex(CopieRac,"2 - Arbre (supprimerSAG)");
    }
    //Remplace le pere de A0 par CopieRac
    if(atoi(argv[1]) == 3){
      A0->RemplacerPourLePerePar(CopieRac);
      SortieLatex(Rac,"3 - Arbre (RemplacerPourlePerePar)");
    }

    //Verifie si Rac; copieRac et A2 sont des feuilles d'arbres
  system("clear");
  std::cout << "Rac->FeuilleP() = " << Rac->FeuilleP() << std::endl
	    << "CopieRac->FeuilleP() = " << CopieRac->FeuilleP() << std::endl
	    << "A2->FeuilleP() = " << A2->FeuilleP() << std::endl;
  }
  else{
    SortieLatex(Rac,"0 - Arbre (base)");
    system("clear");
    std::cout << "Aide du Programme:\n\n"
      
	      << "Ce programme execute des methodes bien precise sur\n"
	      << "un arbre binaire selon l'action choisi par l'utillisateur\n"
	      << "et va ensuite afficher cette arbre sous forme de pdf\n\n"

	      << "L'arbre de base est generé dans le dossier ou est executé ce\n"
	      << "programme sous le nom: 0 - Arbre (base).pdf\n\n"

	      << "Utillisation:\n\n"
      
	      << argv[0] << " <Action>\n\n"
      
      	      << "Action = 1: Execution de SupprimerSAD()\n"
	      << "Affichage -> 1 - Arbre (supprimerSAD).pdf\n\n"
      
	      << "Action = 2: Execution de SupprimerSAG()\n"
	      << "Affichage -> 2 - Arbre (supprimerSAG).pdf\n\n"
    
    	      << "Action = 3: Execution de A0->RemplacerPourlePerePar(copieRac)\n"
	      << "Affichage -> 3 - Arbre (RemplacerPourlePerePar).pdf\n\n";
  }
  return 0;
}


// g++ AB.cpp SortieLatex.cpp -o AB
