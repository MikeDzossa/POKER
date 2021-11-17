#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "Jeu.h"
#include "Mise.h"
extern signed char Nom_J1[15], Nom_J2[15];
extern int possible, Premier, Check, Mise_1, Mise_2, Cash_1, Cash_2, Pot, Joueur, decision, Gagnant, Mise;
extern CARTE Joueur1[7],Joueur2[7];
void Effectuer_Mise() //Effectue la mise d'une somme convenable
 {
     int Erreur=0;
     if(Joueur==1)
     {

        do
        {
            Erreur=0;
            Nettoyer_cadre(6,44,32,32,2); gotoxy(6,32); color(15,0); printf("Entrez le montant de la mise :");
            scanf("%d",&Mise);
            if(Mise_1+Mise<Mise_2) { Nettoyer_cadre(5,44,30,30,2); gotoxy(5,30); color(15,0); printf("Montant insuffisant. Misez plus"); Erreur++;}
            else if(Mise>Cash_1) {Nettoyer_cadre(5,44,30,30,2); gotoxy(5,30); color(15,0); printf("Montant choisit depasse votre bourse"); Erreur++;}
            else if(Mise_1+Mise-Mise_2>Cash_2) {Nettoyer_cadre(5,44,30,30,2); gotoxy(5,30); color(15,0); printf("Mise depasse la bourse adverse. Reduisez"); Erreur++;}
        }
        while(Erreur);
        Cash_1-=Mise;
        Mise_1+=Mise;
        Pot+=Mise;
     }
     else
     {
        do
        {
            Erreur=0;
            Nettoyer_cadre(87,125,32,32,2); gotoxy(87,32); color(15,0); printf("Entrez le montant de la mise : ");
            scanf("%d",&Mise);
            if(Mise_2+Mise<Mise_1) {Nettoyer_cadre(86,125,30,30,2); gotoxy(86,30); color(15,0); printf("Montant insuffisant. Misez plus"); Erreur++;}
            else if(Mise>Cash_2) {Nettoyer_cadre(86,125,30,30,2); gotoxy(86,30); color(15,0); printf("Montant choisit depasse votre bourse"); Erreur++;}
            else if(Mise_2+Mise-Mise_1>Cash_1) {Nettoyer_cadre(86,125,30,30,2); gotoxy(86,30); color(15,0); printf("Mise depasse la bourse adverse. Reduisez"); Erreur++;}
        }
        while(Erreur);
        Cash_2-=Mise;
        Mise_2+=Mise;
        Pot+=Mise;
     }
 }

 void MISE_DEPART(int NumJoueur) //La blinde mise la somme initialement prévu (20$)
{
    Nettoyer_cadre(1,125,10,10,2);
   if(NumJoueur==1)
   {
     if(Cash_1>=20) Mise_1=20;
     else Mise_1=Cash_1;
     Pot+=Mise_1;
     Cash_1-=Mise_1;
     gotoxy(16,10); color(1,0);
     printf("%s LA BLINDE A MISE",Nom_J1);
     Joueur=2;
   }
   else
   {
     if(Cash_2>=20) Mise_2=20;
     else Mise_2=Cash_2;
     Pot+=Mise_2;
     Cash_2-=Mise_2;
     gotoxy(94,10); color(1,0);
     printf("%s LA BLINDE A MISE",Nom_J2);
     Joueur=1;
   }
}

void POSSIBLE() //Vérifie s'il est possible de choisir CHECK
{
 possible=0;
 if(Mise_1==Mise_2||Check) possible++;
}

void Decision() //decision= choix de l'action du joueur 2 ex: miser, se coucher
{
 Nettoyer_cadre(86,125,30,30,2); Nettoyer_cadre(86,125,30,30,2); //Nettoie les emplacements de commentaires
 do
 {
  POSSIBLE(); //Vérifie s'il est possible de choisir CHECK
  if(Joueur==1)
  {
     Nettoyer_cadre(6,44,32,32,2); gotoxy(11,32); color(15,0); printf("Entrez vortre choix : "); scanf("%d",&decision); //Néttoie l'emplacement puis affiche le message
     if(decision==2&&!possible)
     {
         Nettoyer_cadre(86,125,30,30,2); gotoxy(7,30); color(15,0); printf("Impossible, vos mises different");  //Néttoie l'emplacement puis affiche le message
     }
  }
  if(Joueur==2)
  {
     Nettoyer_cadre(87,125,32,32,2); gotoxy(96,32); color(15,0); printf("Entrez vortre choix : "); scanf("%d",&decision);  //Néttoie l'emplacement puis affiche le message
     if(decision==2&&!possible)
     {
         Nettoyer_cadre(86,125,30,30,2); gotoxy(88,30); color(15,0); printf("Impossible, vos mises different");  //Néttoie l'emplacement puis affiche le message
     }
  }
 }
 while((decision!=1&&decision!=3)&&!(decision==2&&possible)); //Tant que la décision n'est pas acceptable
}


 void Lire_Montants() //met à jour les montants dans leurs emplacements
 {
     Nettoyer_cadre(68,73,12,12,2);  //Néttoie l'emplacement du montant du Pot
     gotoxy(68,12); color(15,0); printf("%d$",Pot); //Actuallise le montant
     Nettoyer_cadre(33,38,8,8,2); //Néttoie l'emplacement du montant de la Bourse 1
     gotoxy(33,8); color(15,0); printf("%d$",Cash_1); //Actuallise le montant
     Nettoyer_cadre(113,118,8,8,2); //Néttoie l'emplacement du montant de la Bourse 2
     gotoxy(113,8); color(15,0); printf("%d$",Cash_2); //Actuallise le montant
     Nettoyer_cadre(35,39,13,13,2); //Néttoie l'emplacement du montant de la Mise 1
     gotoxy(35,13); color(15,0); printf("%d$",Mise_1); //Actuallise le montant
     Nettoyer_cadre(112,117,13,13,2); //Néttoie l'emplacement du montant de la Mise 2
     gotoxy(112,13); color(15,0); printf("%d$",Mise_2); //Actuallise le montant
 }

  void Declaration_Gagnant()//Verse le montant du pot dans la bourse du gagnant et affiche le montant remporté
 {
     if(Gagnant==1) //si joueur 1 gagne
     {
         Cash_1+=Pot;
         printf("%s GAGNE : %d$", Nom_J1,Pot);
     }
     else if(Gagnant==2) //si joueur 2 gagne
     {
         Cash_2+=Pot;
         printf("%s GAGNE : %d$", Nom_J2,Pot);
     }
     else if(!Gagnant) //En cas de match nul
     {
         Cash_1+=Pot/2; Cash_2+=Pot/2;
         printf("MANCHE NULLE!\t%s REMPORTE : %d$\t%s REMPORTE : %d$",Nom_J1,Pot/2,Nom_J2,Pot/2);
     }
 }
