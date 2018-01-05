Exercice 1:

a) toutes les méthodes @test appelées dans un ordre quelconques
méthodes @before avant chaque méthode @test

Exercice 3:

a) testBar ne teste rien.

b) problème = pas d'accès aux attributs x, y et z => ajouter des getters.

Rouge: classes test paramétres

@RunWith(paramtrized class) => avant la classe
+ constructeur paramétré

@Parameters
(méthode renvoyant une Collection de paramètres

classes suite de tests

@RunWith(suite.class) => avant la classe

@suite SuiteClasses({A.class, B.class, C.class})
