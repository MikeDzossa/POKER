#ifndef MISE_H_INCLUDED
#define MISE_H_INCLUDED

void Decision(); //decision= choix de l'action du joueur 2 ex: miser, se coucher

void POSSIBLE(); //V�rifie s'il est possible de choisir CHECK

void MISE_DEPART(int NumJoueur); //La blinde mise la somme initialement pr�vu (20$)

void Lire_Montants(); //met � jour les montants dans leurs emplacements

void Declaration_Gagnant(); //Verse le montant du pot dans la bourse du gagnant et affiche le montant remport�

void Effectuer_Mise(); //Effectue la mise d'une somme convenable

#endif // MISE_H_INCLUDED
