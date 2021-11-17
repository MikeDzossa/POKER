#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "Jeu.h"
#include "Mise.h"
#include "Combinaison.h"

int gMax=51, possible=0, Premier, Check, Mise_1=0, Mise_2=0, Cash_1, Cash_2, Pot=0, Joueur=0, decision, Gagnant, Mise, nMise_1, nMise_2, nb_Combi_Joueur1, nb_Combi_Joueur2, n, Compte_final;
signed char Nom_J1[10], Nom_J2[10];
CARTE Joueur1[7],Joueur2[7],Milieu[5], Jeu[52], Tab_Ordre_Croissant[7], Couleur_J1[5], Couleur_J2[5], Tab_Couleur[5], Tab_Quinte[5], J1_Couleur[5], J2_Couleur[5];;
COMBINAISON Combi_Joueur1, Combi_Joueur2;
extern char *TabCombinaisons[];


int main(int argc, char *argv[])
{
 system("mode con LINES=40 COLS=130"); // Précise les dimentions de la console lors de l'exécution
 signed char Continue='N';
 int i, Compte=0;

 srand(time(NULL)); // initialiser le générateur aléatoire
do
{
 Cash_1=200; Cash_2=200;
 system("cls"); system("cmd /c \"color 0f\""); //netoyer l'écran et le peindre en noir
 menu(15,0);
 LIRE_NOMS(); // Recupere le pseudo de chaque joueur pour l'utiliser tout le long
 Type_de_partie(); gotoxy(47,32); system("pause");
 //Permet de choisir un des types de partie
 do
 {
   InitJeu(); // Initialisation du paquet de cartes. 52 cartes dans un ordre précis
   Affectation_Cartes(); //Distribue 2 cartes par joueur et met 5 cartes au milieu

   Compte++; //Compte le nombre de tours jouer dans la partie
   if(Compte%2) { Joueur=1; Premier=2; } else {Joueur=2; Premier = 1;} // Joueur permet d'identifier celui qui est sensé jouer
   Afficher_Cadres(); // Affiche tous les cadres/boxes avec leurs contenus statiques
   Afficher_Cartes(); //affiche les 2 cartes de chaque joueur dans leurs emplacements respectifs
   Nettoyer_cadre(69,73,8,8,2); gotoxy(70,8); color(15,0); printf("%d",Compte);
   Pot=0; Mise_1=0; Mise_2=0; //Initialisation des montants au debut de la manche
   Lire_Montants(); //met à jour les montants dans leurs emplacements
   gotoxy(47,35); system("pause"); Nettoyer_cadre(40,95,35,35,2); //attendre une entrée quelconque pour continuer puis néttoi le message affiché
   MISE_DEPART(Joueur); //La blinde mise la somme initialement prévu (20$)
   Lire_Montants(); //met à jour les montants dans leurs emplacements
   gotoxy(47,35); system("pause"); Nettoyer_cadre(40,95,35,35,2); //attendre une entrée quelconque pour continuer puis néttoi le message affiché
   Gagnant=0; //Ces valeurs sont reinitialisés à chaque manche
   for(i=1;i<=4;i++)// i va de 1 à 4 pour les 4 tours de mise.
   {
       if(!(i==1&&Compte%2)) Mise_1=0;  //Si Joueur 1 n'est pas la blinde
       if(!(i==1&&!(Compte%2))) Mise_2=0;  //Si Joueur 2 n'est pas la blinde
       nMise_1=0; nMise_2=0; Check=0;
       // On initialise les variables qui retourne au néant à chaque tour de mise
     Nettoyer_cadre(73,76,28,28,2); gotoxy(74,28); color(15,0); printf("%d",i); //Affiche le tour de mise dans son emplacement
     if(Premier==1) Joueur=1; //Joueur = 1 ==>c'est le tour de Joueur1   Joueur=2 ==>c'est le tour de joueur2
     else Joueur=2;
     Nettoyer_cadre(5,44,32,32,2); Nettoyer_cadre(5,44,30,30,2); Nettoyer_cadre(87,125,32,32,2); Nettoyer_cadre(86,125,30,30,2); //netoyer les emplacements dédiés aux messages
     do //Début du tour de mise .
     {
        if(Joueur==1) // Si c'est à joueur 1 de jouer...
        {
          nMise_1++;   //nMise1= Compteur de nombre de mise effectuées par joueur 1 par tour de mise.
          Nettoyer_cadre(1,125,10,10,2); gotoxy(16,10); color(1,0); printf("%s A VOUS DE JOUER",Nom_J1); //affiche le message à l'endroi indiqué après avoir nétoyé son contenu précédent
          Decision();  //decision= choix de l'action du joueur 1 ex: miser, se coucher
          switch(decision)
          {
             case 1: //miser oblige à metre de l'argent dans le pot
                Effectuer_Mise(); //Effectue la mise d'une somme convenable
                Lire_Montants(); //met à jour les montants dans leurs emplacements
                Check=0;
                break;

             case 2:
                 Check++;  //Check équivaut à passer son tour.
                 Nettoyer_cadre(5,44,30,30,2); gotoxy(19,30); color(15,0); printf("JE CHECK");
                break;

             case 3:
                Gagnant=2; //Abandonner
                Nettoyer_cadre(5,44,30,30,2); gotoxy(15,30); color(15,0); printf("%s ABANDONNE",Nom_J1);
                break;
          }
          Joueur=2;
        }
        if(Joueur==2&&((Mise_2<Mise_1)||nMise_2<1)&&!Gagnant) //Si c'est à Joueur 2 de jouer et qu_il n'a pas misé ou les montants de mises sont différentes...
        {
          nMise_2++;
          Nettoyer_cadre(1,125,10,10,2); color(1,0); gotoxy(95,10); printf("%s A VOUS DE JOUER",Nom_J2); //affiche le message à l'endroi indiqué après avoir nétoyé son contenu précédent
          Decision(); //decision= choix de l'action du joueur 2 ex: miser, se coucher
          switch(decision)
          {
             case 1:  //miser oblige à metre de l'argent dans le pot
                Effectuer_Mise(); //Effectue la mise d'une somme convenable
                Lire_Montants(); //met à jour les montants dans leurs emplacements
                Check=0;
                break;

             case 2:
                 Check++; //Check équivaut à passer son tour.
                 Nettoyer_cadre(86,125,30,30,2); gotoxy(100,30); color(15,0); printf("JE CHECK");
                break;

            case 3:
                Gagnant=1; //Abandonner
                Nettoyer_cadre(86,125,30,30,2); gotoxy(96,30); color(15,0); printf("%s ABANDONNE",Nom_J2);
                break;
          }
          Joueur=1;
        }
     }
     while((Mise_1!=Mise_2||(!nMise_1||!nMise_2))&&!Gagnant);//Tant que mises différentes ou l'un n'a pas encore joué.
     if(Gagnant) {gotoxy(47,35); system("pause"); Nettoyer_cadre(40,95,35,35,2); break;}
     Retourner_Cartes_Milieu(i); //Affiche une ou plusieurs cartes du millieu selon le tour de mise
   }
    system("cls");
    system("cmd /c \"color 0f\""); //peindre l'écran tout en noir
    Nettoyer_cadre(10,120,10,25,2); //peindre la plage selectionée en vert
   if(Gagnant) //si l'un s'est couché en cours de mise
   {
       if(Gagnant==1)
       {
           gotoxy(40,15); color(15,2); printf("%s REMPORTE LA MISE\t",Nom_J1); Declaration_Gagnant(); //Verse le montant du pot dans la bourse du gagnant et affiche le montant remporté
           gotoxy(40,20); color(4,2); printf("%s S'EST COUCHE",Nom_J2);
       }
        else
       {
           gotoxy(40,15); color(4,2); printf("%s S'EST COUCHE",Nom_J1);
           gotoxy(40,20); color(15,2); printf("%s REMPORTE LA MISE\t",Nom_J2); Declaration_Gagnant(); //Verse le montant du pot dans la bourse du gagnant et affiche le montant remporté
       }
   }
   else if(!Gagnant) //si aucun ne s'est couché
   {
        Ordre_Croissant(Joueur1,7); //classe les cartes en ordre croissant dans un tableau intermediaire
        for(i=0;i<7;i++) //remet les cartes ordonnées dans la main du joueur
        {
           Joueur1[i]=Tab_Ordre_Croissant[i];
        }
        Ordre_Croissant(Joueur2,7); //classe les cartes en ordre croissant dans un tableau intermediaire
        for(i=0;i<7;i++) //remet les cartes ordonnées dans la main du joueur
        {
           Joueur2[i]=Tab_Ordre_Croissant[i];
        }
        Verif_Combinaisons(Joueur1); //vérifie toutes les combinaisons possibles dans la main
        Attribue_Combinaison(1); //sauvegarde la meilleure combinaison dans la variable combinaison du joueur
        Verif_Combinaisons(Joueur2); //vérifie toutes les combinaisons possibles dans la main
        Attribue_Combinaison(2); //sauvegarde la meilleure combinaison dans la variable combinaison du joueur
        Assigner_Gagnant(); //Compare les meilleurs combinaisons des 2 joueurs et désigne le vainqueur
        gotoxy(12,14); color(3,2); printf("%s",Nom_J1); Lire_Cartes(7, Joueur1);
        gotoxy(12,16); color(3,2); printf("Combinaison %s = ",Nom_J1); color(4,2); printf("%s",TabCombinaisons[nb_Combi_Joueur1]); Lire_Combinaisons(nb_Combi_Joueur1,Combi_Joueur1);
        gotoxy(12,20); color(3,2); printf("%s",Nom_J2); Lire_Cartes(7, Joueur2);
        gotoxy(12,22); color(3,2); printf("Combinaison %s = ",Nom_J2); color(4,2); printf("%s",TabCombinaisons[nb_Combi_Joueur2]); Lire_Combinaisons(nb_Combi_Joueur2,Combi_Joueur2);
        //les instructions plus haut affichent les cartes et les combinaisons de chacun à l'emplacement indiqué
         gotoxy(20,24); color(15,2);
        if(Gagnant==1) printf("%s REMPORTE LA MISE\t",Nom_J1);
        else if(Gagnant==2) printf("%s REMPORTE LA MISE\t",Nom_J2);
        Declaration_Gagnant(); //Verse le montant du pot dans la bourse du gagnant et affiche le montant remporté
    }
   gotoxy(45,27); system("pause"); //attendre une entrée quelconque pour continuer
 }
 while(Cash_1!=0&&Cash_2!=0&&Compte<Compte_final);
 Nettoyer_cadre(10,120,28,36,15); gotoxy(42,30); color(0,15); printf("BOURSE %s : %d\tBOURSE %s : %d",Nom_J1,Cash_1,Nom_J2,Cash_2);
 gotoxy(30,32); color(3,15);
 if(Cash_2<Cash_1)
    printf("-----------------[ %s GAGNE LA PARTIE DE POKER ]-----------------",Nom_J1);
 else if(Cash_2>Cash_1)
    printf("-----------------[ %s GAGNE LA PARTIE DE POKER ]-----------------",Nom_J2);
 else printf("\t\t------------------[ MATCH NULL ]------------------");
 gotoxy(48,34); color(4,15); printf("MERCI D'UTILISER NOTRE PROGRAMME");
  gotoxy(43,38); printf("ENTREZ 'Y'/'y' POUR UNE NOUVELLE PARTIE : "); scanf("%s",&Continue);
}
while(Continue=='Y'||Continue=='y');
gotoxy(43,39); return 0;

}

