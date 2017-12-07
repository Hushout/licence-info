char villes[41][20]={"Amiens", "Angouleme", "Avignon", "Bayonne", "Bilbao", "Bordeaux", "Bourges", "Brest", "Brive", "Bruxelles", "Caen", "Cahors", "Clermont-Ferrand", "Dijon", "Geneve", "Grenoble", "Lille", "Limoges", "Luxembourg", "Lyon", "Marseille", "Millau", "Montpellier", "Mulhouse", "Nancy", "Nantes", "Nice", "Orleans", "Paris", "Perpignan", "Poitiers", "Reims", "Rennes", "Rodez", "Rouen", "Saint-Etienne", "Strasbourg", "Toulouse", "Tours", "Troyes", "Valence"};

int position[41][2]={{282,84},{180,334},{412,443},{140,455},{80,480},{165,389},{304,253},{14,150},{249,365},{380,15},{182,117},{258,412},{322,322},{408,231},{470,287},{464,359},{324,32},{242,332},{470,60},{405,306},{433,480},{339,440},{365,461},{497,208},{453,148},{116,233},{515,460},{277,194},{296,146},{329,505},{208,271},{369,119},{120,175},{330,410},{228,101},{383,339},{508,152},{227,466},{220,230},{363,179},{408,377}};

void initlongueur(int longueur[][41]){
	int inf = 9999;

	for(int i=0;i<41;i++){
		for(int j=0;j<41;j++){
			longueur[i][j]=inf;
		}
		longueur[i][i]=0;
	}

	longueur[0][34]=120; longueur[0][28]=130;
	longueur[0][31]=180; longueur[0][16]=140;

	longueur[1][30]=130;  longueur[1][17]=110;
	longueur[1][8]=170;  longueur[1][5]=120;

	longueur[2][40]=140;  longueur[2][22]=90;
	longueur[2][20]=90;

	longueur[3][5]=180;  longueur[3][37]=300;
	longueur[3][4]=70;	longueur[4][3]=70;

	longueur[5][1]=120; longueur[5][8]=200; longueur[5][11]=230; 
	longueur[5][37]=241; longueur[5][3]=180;

	longueur[6][27]=121; longueur[6][39]=240; longueur[6][13]=250; 
	longueur[6][12]=190; longueur[6][38]=230;

	longueur[7][32]=240;

	longueur[8][11]=101; longueur[8][17]=100; longueur[8][1]=170; 
	longueur[8][5]=200; longueur[8][33]=140;

	longueur[9][16]=110; longueur[9][31]=230; longueur[9][18]=210;

	longueur[10][34]=130; longueur[10][38]=260; longueur[10][32]=180;

	longueur[11][21]=180; longueur[11][8]=101; longueur[11][5]=230; 
	longueur[11][37]=110; longueur[11][33]=105;

	longueur[12][6]=190; longueur[12][19]=210; longueur[12][35]=150; 
	longueur[12][17]=230; longueur[12][33]=270;

	longueur[13][19]=200; longueur[13][23]=221; longueur[13][24]=220; 
	longueur[13][39]=180; longueur[13][6]=250; longueur[13][14]=200;

	longueur[14][15]=145; longueur[14][19]=150; longueur[14][13]=200;

	longueur[15][26]=340; longueur[15][20]=270; longueur[15][40]=90; 
	longueur[15][19]=150; longueur[15][14]=145;

	longueur[16][0]=140; longueur[16][31]=196; longueur[16][9]=110;

	longueur[17][30]=120; longueur[17][1]=110; longueur[17][8]=100; 
	longueur[17][12]=230;

	longueur[18][31]=218; longueur[18][36]=220; longueur[18][9]=210; 
	longueur[18][24]=200;

	longueur[19][40]=150; longueur[19][35]=80; longueur[19][12]=210; 
	longueur[19][13]=200; longueur[19][14]=150; longueur[19][15]=150;

	longueur[20][22]=170; longueur[20][2]=90; longueur[20][26]=200; 
	longueur[20][15]=270;

	longueur[21][37]=190; longueur[21][11]=180; longueur[21][22]=110; 
	longueur[21][33]=60;

	longueur[22][29]=150; longueur[22][37]=240; longueur[22][21]=110; 
	longueur[22][2]=90; longueur[22][20]=170; longueur[22][40]=200;

	longueur[23][13]=221; longueur[23][24]=170; longueur[23][36]=120;

	longueur[24][36]=160; longueur[24][23]=170; longueur[24][13]=220; 
	longueur[24][31]=240; longueur[24][18]=200;

	longueur[25][32]=110; longueur[25][38]=210; longueur[25][30]=220;

	longueur[26][20]=200; longueur[26][15]=340;

	longueur[27][6]=121; longueur[27][39]=200; longueur[27][28]=132; 
	longueur[27][38]=120;

	longueur[28][0]=130; longueur[28][34]=131; longueur[28][27]=132; 
	longueur[28][39]=181; longueur[28][31]=140;

	longueur[29][37]=210; longueur[29][22]=150;

	longueur[30][25]=220; longueur[30][38]=100; longueur[30][17]=120; 
	longueur[30][1]=130;

	longueur[31][24]=240; longueur[31][28]=140; longueur[31][39]=130; 
	longueur[31][0]=180; longueur[31][16]=196; longueur[31][9]=230; 
	longueur[31][18]=218;

	longueur[32][10]=180; longueur[32][38]=250; longueur[32][7]=240; 
	longueur[32][25]=110;

	longueur[33][35]=200; longueur[33][40]=225; longueur[33][21]=60; 
	longueur[33][8]=140; longueur[33][11]=105; longueur[33][12]=270;

	longueur[34][0]=120; longueur[34][28]=131; longueur[34][10]=130;

	longueur[35][12]=150; longueur[35][19]=80; longueur[35][40]=120; 
	longueur[35][33]=200;

	longueur[36][23]=120; longueur[36][24]=160; longueur[36][18]=220;

	longueur[37][3]=300; longueur[37][5]=241; longueur[37][11]=110; 
	longueur[37][21]=190; longueur[37][22]=240; longueur[37][29]=210;

	longueur[38][10]=260; longueur[38][32]=250; longueur[38][25]=210; 
	longueur[38][30]=100; longueur[38][27]=120; longueur[38][6]=230;

	longueur[39][31]=130; longueur[39][28]=181; longueur[39][27]=200; 
	longueur[39][6]=240; longueur[39][13]=180;

	longueur[40][2]=140; longueur[40][15]=90; longueur[40][35]=120; 
	longueur[40][19]=150; longueur[40][33]=225; longueur[40][22]=200;
}

