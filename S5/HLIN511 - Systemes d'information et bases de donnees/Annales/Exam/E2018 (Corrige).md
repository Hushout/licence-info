# Exercice 1

#### Question 1

```
/--------------\                                /--------------\
|Discipline    |                                |Categorie     |
|--------------| 1,1                        1,n |--------------|
|idDis         |----------(appartient_à)--------|idCat         |
|-----         |                                |-----         |
|designation   |                                |designation   |
\--------------/                                \--------------/
      |         \___ 0,n
      | 0,n         \___
      |                 \
(participe_seul)       (participe_equipe)
      |                                \___
      | 0,n                                \___ 1,n
      |                                        \ 
/--------------\                                /--------------\
|Athlète       |                                |Equipe        |
|--------------| 1,n                        2,n |--------------|
|idAth         |----------(est_membre)----------|idEqu         |
|-----         |                                |-----         |
|nom           |                                |nom           |
|prenom        |                                \--------------/
|genre         |
|date_naissance|
|pays          |
\--------------/
```

#### Question 2
```sql
CREATE TABLE Athlete (
	idAth NUMBER(6),
	nom VARCHAR(32),
	prenom VARCHAR(32),
	genre CHAR(1),
	date_naissance DATE,
	pays VARCHAR(32),
	CONSTRAINT PK_ATHLETE PRIMARY KEY(idAth),
	CONSTRAINT CK_GENRE CHECK genre IN ('A', 'F')
);

CREATE TABLE Equipe (
	idEqu NUMBER(6),
	designation VARCHAR(32),
	CONSTRAINT PK_EQUIPE PRIMARY KEY(idEqu)
);

CREATE TABLE Categorie (
	idCat NUMBER(6),
	designation VARCHAR(20),
	CONSTRAINT PK_CATEGORIE PRIMARY KEY(idCat)
);

CREATE TABLE Discipline (
	idDis NUMBER(6),
	designation VARCHAR(20),
	CONSTRAINT PK_DISCIPLINE PRIMARY KEY(idDis)
);

CREATE TABLE appartient_à (
	idDis NUMBER(6),
	idCat NUMBER(6),
	CONSTRAINT PK_APPARTIENT_A PRIMARY KEY(idDis, idCat),
	CONSTRAINT FK_APPARTIENT_DIS FOREIGN KEY(idDis) 
		REFERENCES Discipline(idDis),
	CONSTRAINT FK_APPARTIENT_CAT FOREIGN KEY(idCat) 
		REFERENCES Categorie(idCat),
);

CREATE TABLE participe_seul (
	idDis NUMBER(6),
	idAth NUMBER(6),
	CONSTRAINT PK_PARTICIPE_SEUL PRIMARY KEY(idDis, idAth),
	CONSTRAINT FK_PARTICIPE_SEUL_DIS FOREIGN KEY(idDis) 
		REFERENCES Discipline(idDis),
	CONSTRAINT FK_PARTICIPE_SEUL_ATH FOREIGN KEY(idAth) 
		REFERENCES Athlete(idAth),
);

CREATE TABLE participe_equipe (
	idEqu NUMBER(6),
	idDis NUMBER(6),
	CONSTRAINT PK_PARTICIPE_EQUIPE PRIMARY KEY(idDis, idEqu),
	CONSTRAINT FK_PARTICIPE_EQUIPE_DIS FOREIGN KEY(idDis) 
		REFERENCES Discipline(idDis),
	CONSTRAINT FK_PARTICIPE_EQUIPE_ATH FOREIGN KEY(idEqu) 
		REFERENCES Equipe(idEqu),
);

CREATE TABLE est_membre (
	idAth NUMBER(6),
	idEqu NUMBER(6),
	CONSTRAINT PK_EST_MEMBRE PRIMARY KEY(idAth, idEqu),
	CONSTRAINT FK_EST_MEMBRE_ATH FOREIGN KEY(idAth) 
		REFERENCES Athlete(idAth),
	CONSTRAINT FK_EST_MEMBRE_EQU FOREIGN KEY(idEqu) 
		REFERENCES Equipe(idEqu),
);
```

#### Question 3

Ce trigger verfie avant d'inserer un membre (un athlete dans un equipe)
le nombre d'athlète dans l'équipe en question qui n'ont pas la même nationalité que l'athlète.
Si on trouve 1 ou plusieurs athlètes n'ayant pas la même nationalité on envoie une exception.

NOM_A_TROUVER: verif_nationalité_athlète
MESSAGE_A_TROUVER: "L'athlète n'est pas dans son equipe nationale"

En résumé : On ne mettrait des athlètes français que dans des equipes françaises.

# Exercice 2

#### Question 1

1. 
```sql
SELECT adresse, SUM(mention_remboursement)
FROM remboursement
GROUP BY adresse
```

2. 	
```sql
SELECT d_emprenteur 
FROM remboursement R1 
WHERE NOT EXISTS (SELECT * 
    FROM remboursement R2 
	WHERE R1.adresse = R2.adresse 
	AND R1.id_emprunteur <> R2.id_emprunteur)
```

3.
```sql
DELETE FROM remboursement
WHERE (id_emprunteur, montant_emprunte, date_demande) 
IN (SELECT id_emprunteur, montant_emprunte, date_demande
	FROM remboursement
	GROUP BY id_emprunteur, montant_emprunte, date_demande
	HAVING SUM(montant_remboursement) = montant_emprunte)
```

#### Question 2

id_emprunteur -> nom
id_emprunteur -> adresse
id_emprunteur, date_demande -> montant_emprunte
date_remboursement, id_emprunteur, date_demande -> montant_rembourse

id_emprunteur, date_demande et date_remboursement ne sont jamais à droite d'une dependance foncionnell ils sont donc dans la clé

Fermeture transitive:
(date_remboursement, id_emprunteur, date_demande) +
= (nom, adresse, montant_emprunte, montant_rembourse, date_remboursement, date_demande, id_emprunteur)

On a bien (id_emprunteur, date_demande et date_remboursement) comme clé primaire.

#### Question 3

En NF:

R1(__id_emprunteur__, nom, adresse)
R2(__id_emprunteur, date_demande__, montant_emprunte)
R3(__id_emprunteur, date_demande, date_remboursement__, montant_rembourse)

#### Question 4

|    | id | nom        | adresse    | dD  | dR  | mR  | mE         |
|----|----|------------|------------|-----|-----|-----|------------|
| R1 | a1 | a2         | a3         | b14 | b15 | b16 | b17        |
| R2 | a1 | ~~b22~~ a2 | ~~b23~~ a3 | a4  | b25 | b26 | a7         |
| R3 | a1 | ~~b32~~ a2 | ~~b33~~ a3 | a4  | a5  | a6  | ~~b37~~ a7 |

Etape 1: id -> nom
	R1: a1 -> a2
	R2: a1 -> ~~b22~~ a2
	R3: a1 -> ~~b32~~ a2

Etape 2: id -> adresse
	R1: a1 -> a3
	R2: a1 -> ~~b24~~ a3
	R3: a1 -> ~~b34~~ a3

Etape 3: id -> adresse
	R2: a1, a4 -> a7
	R3: a1, a4 -> ~~b47~~ a7

On a une ligne avec que des 'a' donc pas de perte d'informations