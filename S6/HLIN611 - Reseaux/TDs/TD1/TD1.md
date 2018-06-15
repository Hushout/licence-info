**Exercice 1:**

1Kib = 1024 bits
1Gio = 1024x1024x1024 octets

1.a) 1024x1024x32 bits = 32Mib
	x10 = 320Mib

b) Modem années 90: débit 55 600 b/s
temps minimal: 320x1024x1024 / 55 600 = 6035s =~ 1h40

Adsl: 1Mib/s
	320 Mib à 1Mib/s => 320s =~ 5'30

Fac de science: 10Mib/s => 32s

Débit théorique
Il faut compter les "info" rejetés par la transmission

2.a) Débit moyen: 25/(25x40+300) = 25/(25x(40+12)) = 1/52 = 0.019 c/ms = 19 c/s
Début crète: 1/40 = 0,025 c/ms = 25 c/s

(c = client)

Temps moyen d'arrivée d'info: (10x1024 + 24x250)/(25x40 + 300) = 12,49 o/ms =~ 12 490 o/s =~ 12kio/s

Temps d'affichage: 50µs => 1octet => debit de traitement: 1/50 o/µs = 0,02 o/µs = 20000 o/s =~ 20Ko/s =~ 20Kio/s

Taux de charge: taux arr moyen / temps d'affichage = 12/20 = 60%

**Exercice 2:**

1 Cellule = 53 octets

Débit: 53x8/500x10^-6 = 424/5x10^⁻4 =~ 80/1x10^-4 =~ 848000 b/s =~ 848Kb/s

2) Temps moyen à utilliser pour envoyer une cellule: 53x8/50000 =~ 424/50000 =~ 80/10^4 = 8ms
Temps reel d'envoi d'une cellule = 500µs

Dt = 8000 - 500 = 7500µs 

3) 

4) Connexion acceptable: 0,9 * nbCellules
Moyenne temps cellule: 0,9 * 120 + 0,1 * 200 = 128ms
Decalage minimal: 0, 9 * nbCellules x 30 * 10 ^ ⁻6 + 128 * 10 ^ - 3 =~ nbCellules * 2.7*10^-5 + 128*10^-3

