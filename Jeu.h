#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
typedef struct _CARTE_
{
 int valeur; // 0 � 13 pour As, 2,3... � Joker
 int couleur;// 0 � 5 pour macabo noir, arrachide, biscuit, coeur, noir, rouge
}
CARTE;

void InitJeu(); // Initialisation du paquet de cartes. 52 cartes dans un ordre pr�cis

CARTE *Distribue(CARTE *pCarte); //Tire une carte al�atoirement dans le paquet sans r�p�tition

void Affectation_Cartes(); //Distribue les cartes tir�s aux joueurs et sur la table

void Lire_Cartes(int n,CARTE card1[7]); //afficher toutes les 2 cartes du joueur plus les 5 de la table c�te-�c�te

void LIRE_NOMS(); // Recupere le pseudo de chaque joueur pour l'utiliser tout le long

void Retourner_Cartes_Milieu(int i); //Affiche une ou plusieurs cartes du millieu selon le tour de mise

void Inverser_Cartes(CARTE *Card1, CARTE *Card2); //Permet de choisir un des types de partie

void Type_de_partie(); //Permet de choisir un des types de partie

void Afficher_Cadres(); // Affiche tous les cadres/boxes avec leurs contenus statiques

void Nettoyer_cadre(int x1, int x2, int y1, int y2, int bgc); //Permet de repeindre une selection de une couleur donn�e

void menu(int c,int bgc); // Affiche le titre du jeu en des couleurs sp�cifi�s

void ligne_Verticale(int x, int y1, int y2, int c, int b); //trace une ligne verticale de y1+1 � y2-1 de couleur c et zrriere-plan b

void ligne_Horizontale(int x1, int x2, int y, int c, int b); //trace une ligne horizontale de x1+1 � x2-1 de couleur c et zrriere-plan b

void cadre(int x1,int x2,int y1,int y2,int cfg, int cbg); //trace un cadre carr� de x1 � x2 sur l'horizontale et de y1 � y2 sur la verticale

void color(int couleurDeTexte,int couleurDeFond); //texte qui suit en couleur couleurDeTexte et de de couleur de font couleurDeFond

void gotoxy(int x, int y); //Met le curseur au point de coordon�es (x,y) pour entrer des valeurs ou afficher

void Afficher_Cartes(); //Affiche les cartes de chaque joueur dans leurs emplacements respectives

#endif // HEADER_H_INCLUDED
