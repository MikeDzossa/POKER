#ifndef COMBI_H_INCLUDED
#define COMBI_H_INCLUDED

typedef struct _COMBINAISON_
{
 int valide; // 0 si non et 1 si elle est valide
 int valeur; // la valeure de la carte maitresse de la combinaison
 int couleur; //la couleur de la combinaison si nécessaire
}
COMBINAISON;
/*
   Combinaison.couleur sera utilisé pour garder la valeur secondaire dans les combinaisons suivantes
   1. La pair : Pair.couleur = valeur de la plus petite pair, Pair.valeur = valeur de la plus grande pair
   2. La full_house : Full_House.couleur = valeur de la pair, Full_House.valeur = valeur du Brelan
*/

void Ordre_Croissant(CARTE Card1[7], int Nombre_cartes); //classe les cartes en ordre croissant dans un tableau intermediaire

void Couleur_Verif(CARTE Card1[7], int Nombre_cartes); // Verifie les cartes de meme couleurs pour former une couleur

void Init_Validiter(); //Initialise la validité de toutes les combinaisons à 0

void Verif_meme_valeur(CARTE Card1[7]); // Compte toutes les cartes d'une main ayant la meme valeur affin de désigner des paires(3), des brelans(2) ou un Carré

void Pair_DbPair_Brelan_FullHouse(); // Compare les resultats précédents pour trouver la meilleure des paires sur 3 possibles, le meilleur brelan sur 2 possibles, la formation d'une double pair et d'une Fullhouse

void Verif_Combinaisons(CARTE Card1[7]); //vérifie toutes les combinaisons possibles dans la main

void Quinte_QuinteFlush_QuinteFlushRoyale(CARTE Card1[7]);

void Attribue_Combinaison(int Joueur); //sauvegarde la meilleure combinaison dans la variable combinaison du joueur

void Assigner_Gagnant(); //Compare les meilleurs combinaisons des 2 joueurs et désigne le vainqueur

void Double_Quinte(); //Compare les 2 quintes pour trouver la plus forte

void Double_Carre_Brelan_ou_Pair(); //Compare les 2 Pairs/Brelan/Carrés pour trouver la plus forte

void Mettre_Combinaison_en_fin(int nbCartes); //Renvoi les carte de la combinaison aux derniers emplacement de la main

void Carte_La_Plus_Forte(int nbCartes); //Fait un nombre(nbCartes) de comparaisons 2 à 2 des cartes des 2 mains ayant le meme emplacement

void Double_FullHouse_DoublePair(); //Compare les 2 FullHouse/DoublePairs pour trouver la plus forte

void Double_Couleur(); //Compare les 2 Couleurs pour trouver la plus forte

void Lire_Combinaisons(int nbCombi, COMBINAISON Combi); //Affiche la valeur ou la couleur de la combinaison

#endif // COMBI_H_INCLUDED
