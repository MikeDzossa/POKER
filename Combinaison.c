#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Jeu.h"
#include "Combinaison.h"
#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

extern CARTE Tab_Ordre_Croissant[7], Tab_Couleur[5], Tab_Quinte[5], J1_Couleur[5], J2_Couleur[5], Joueur1[7], Joueur2[7];
COMBINAISON Pair[3], Db_Pair, Brelan[2], Quinte, Couleur, Full_house, Carre,  Quinte_flush, Quinte_flush_royal, Combi_Joueur1, Combi_Joueur2;
extern char *TabCouleur[], *TabValeur[];
char *TabCombinaisons[]={"Main Forte", "Paire", "Double Paire", "Brelan", "Quinte", "Couleur", "Full House", "Carre", "Quinte Flush", "Quinte Flush Royale"};
extern int nb_Combi_Joueur1, nb_Combi_Joueur2, Gagnant;

void Init_Validiter()  //Initialise la validité des combinaisons.
{
    int i;
    for(i=0;i<=2;i++)
    {
       Pair[i].valide=0;
       if(i<2) Brelan[i].valide=0;
       if(i<1)
       {
           Db_Pair.valide=0;
           Quinte.valide=0;
           Couleur.valide=0;
           Full_house.valide=0;
           Carre.valide=0;
           Quinte_flush.valide=0;
           Quinte_flush_royal.valide=0;
       }
    }
}

void Ordre_Croissant(CARTE Card1[7], int Nombre_cartes) //Classe les cartes d'une main en ordre croissant
{
    Nombre_cartes--;
    int i, j, n=Nombre_cartes, position_petite=0, p_petite_val;
    for(i=0;i<=n;i++)
    {
        p_petite_val=20;
        for(j=0;j<=Nombre_cartes;j++)
        {
            if(Card1[j].valeur<p_petite_val)
            {
                p_petite_val=Card1[j].valeur;
                position_petite=j;
            }
        }
        Tab_Ordre_Croissant[i]=Card1[position_petite];
        Card1[position_petite]=Card1[Nombre_cartes];
        Nombre_cartes--;
    }
}

void Couleur_Verif(CARTE Card1[7], int Nombre_cartes) //Cherche les cartes de meme couleur dans une main pour former une couleur
{
    int i, j, Meme_couleur;
    Nombre_cartes--;
    for(i=0;i<4;i++)
    {
        Couleur.couleur=i; Meme_couleur=0;
        for(j=Nombre_cartes;j>=0;j--)
        {
            if(Card1[j].couleur==i&&Meme_couleur<5)
            {
                Meme_couleur++; Tab_Couleur[5-Meme_couleur]=Card1[j];
            }
            if(Meme_couleur>=5) break;
        }
        if(Meme_couleur>=5)
        {
            Couleur.valide=1; Couleur.valeur=Tab_Couleur[0].valeur;
            break;
        }
    }
}

void Verif_meme_valeur(CARTE Card1[7]) //Cherche les cartes d'une main ayant la meme valeur et valide Pair, Brelan...dans une main
{  // Compte toutes les cartes d'une main ayant la meme valeur affin de désigner des paires(3), des brelans(2) ou un Carré
   int Compte_mem_valeur=0, i;
   for(i=0;i<6;i++)
   {
       if((Card1[i+1].valeur-Card1[i].valeur==0)&&i!=5)
        {
           Compte_mem_valeur++;
        }
       else
       {
           if((Card1[i+1].valeur-Card1[i].valeur==0)&&i==5)
           {
              Compte_mem_valeur++;
           }
           if(Compte_mem_valeur==1)
           {
              if(!Pair[0].valide) { Pair[0].valide=1; Pair[0].valeur=Card1[i].valeur; }
              else if(!Pair[1].valide) { Pair[1].valide=1; Pair[1].valeur=Card1[i].valeur; }
              else { Pair[2].valide=1; Pair[2].valeur=Card1[i].valeur; }
           }
           else if(Compte_mem_valeur==2)
           {
               if(!Brelan[0].valide) { Brelan[0].valide=1; Brelan[0].valeur=Card1[i].valeur; }
               else {Brelan[1].valide=1; Brelan[1].valeur=Card1[i].valeur; }
           }
           else if(Compte_mem_valeur==3)
           {
               Carre.valide=1; Carre.valeur=Card1[i].valeur;
           }
           Compte_mem_valeur=0;
       }
   }
}

void Pair_DbPair_Brelan_FullHouse() //Finalise le resultat précedent en validant la meilleures combinaisons
{ // Compare les resultats précédents pour trouver la meilleure des paires sur 3 possibles, le meilleur brelan sur 2 possibles, la formation d'une double pair et d'une Fullhouse
     if(Brelan[1].valide) //Si on a 2 brelans, mettre plus grand brelan dans Brelan[0]
   {
     if(max(Brelan[0].valeur,Brelan[1].valeur)==Brelan[1].valeur)
         Brelan[0]=Brelan[1];
   }

   if(Pair[2].valide) //Si on a 3 pairs
   {
       Db_Pair.valide=1;
       if(min(min(Pair[0].valeur,Pair[1].valeur),Pair[2].valeur)==Pair[0].valeur) //si la plus petite des valeurs des 3 pairs = ...
       {
           Db_Pair.couleur=Pair[1].valeur; Db_Pair.valeur=Pair[2].valeur; //Db_pair = Pair[1] + Pair[2]
       }
       if(min(min(Pair[0].valeur,Pair[1].valeur),Pair[2].valeur)==Pair[1].valeur)
       {
           Db_Pair.couleur=Pair[0].valeur; Db_Pair.valeur=Pair[2].valeur;  //Db_pair = Pair[0] + Pair[2]
       }
       if(min(min(Pair[0].valeur,Pair[1].valeur),Pair[2].valeur)==Pair[2].valeur)
       {
           Db_Pair.couleur=Pair[0].valeur; Db_Pair.valeur=Pair[1].valeur; //Db_pair = Pair[1] + Pair[0]
           //Db_pair.couleur garde la valeur de la plus petite des 2 paires pair
       }
   }
   else if(Pair[1].valide) //si on a 2 pairs
   {
       Db_Pair.valide=1;
       Db_Pair.couleur=Pair[0].valeur; Db_Pair.valeur=Pair[1].valeur;
       if(Brelan[0].valide)
       {
           if(max(Pair[0].valeur,Pair[1].valeur)==Pair[1].valeur)
                Pair[0]=Pair[1];
           Full_house.valide=1;
           Full_house.valeur=Brelan[0].valeur; Full_house.couleur=Pair[0].valeur;
       }
   }
   else if(Pair[0].valide&&Brelan[0].valide)
   {
           Full_house.valide=1;
           Full_house.valeur=Brelan[0].valeur; Full_house.couleur=Pair[0].valeur;
   }
}

void Quinte_QuinteFlush_QuinteFlushRoyale(CARTE Card1[7]) //Verifie si on a une quinte, quinte_flush... dans une main
{
  int i, j, Meme_couleur, Compte_suite=0;
  for(i=5;i>=0;i--)
   {
       if((Card1[i+1].valeur-Card1[i].valeur==1)&&Compte_suite<4)
        {
           Compte_suite++;
           Tab_Quinte[5-Compte_suite]=Card1[i+1]; Tab_Quinte[4-Compte_suite]=Card1[i];
        }
       else Compte_suite=0;
       if(Compte_suite==4) break;
   }
   if(Compte_suite==4)
   {
     Quinte.valide=1; Quinte.valeur=Tab_Quinte[4].valeur;
     for(i=0;i<4;i++)
     {
        Meme_couleur=0;
        for(j=0;j<5;j++)
        {
            if(Tab_Quinte[j].couleur==i&&Meme_couleur<5)
            {
                Meme_couleur++;
            }
        }
        if(Meme_couleur==5)
        {
            Quinte_flush.valide=1; Quinte_flush.couleur=i; Quinte_flush.valeur=Quinte.valeur;
            if(Tab_Quinte[4].valeur==12) {Quinte_flush_royal.valide=1; Quinte_flush_royal.couleur=i; Quinte_flush_royal.valeur=12;}
            break;
        }
    }

   }
}

void Verif_Combinaisons(CARTE Card1[7]) // Aplique les fonctions précedentes pour trouver toutes les combinaisons possible dans une main
{
    Init_Validiter();
    Verif_meme_valeur(Card1);
    Pair_DbPair_Brelan_FullHouse();
    Couleur_Verif(Card1,7);
    Quinte_QuinteFlush_QuinteFlushRoyale(Card1);
}

void Attribue_Combinaison(int Joueur) // Attribut la meilleur combinaison au Joueur(1 ou 2) Utilisé apres la fonction précédente
{
  int i;
  if(Joueur==1)
  {
    if(Quinte_flush_royal.valide)
    {
       nb_Combi_Joueur1=9; Combi_Joueur1=Quinte_flush_royal;
    }
    else if(Quinte_flush.valide)
    {
        nb_Combi_Joueur1=8; Combi_Joueur1=Quinte_flush;
    }
    else if(Carre.valide)
    {
        nb_Combi_Joueur1=7; Combi_Joueur1=Carre;
    }
    else if(Full_house.valide)
    {
        nb_Combi_Joueur1=6; Combi_Joueur1=Full_house;
    }
    else if(Couleur.valide)
    {
        nb_Combi_Joueur1=5; Combi_Joueur1=Couleur;
        for(i=0;i<5;i++)
        {
           J1_Couleur[i]=Tab_Couleur[i];
        }
    }
    else if(Quinte.valide)
    {
        nb_Combi_Joueur1=4; Combi_Joueur1=Quinte;
    }
    else if(Brelan[0].valide)
    {
        nb_Combi_Joueur1=3; Combi_Joueur1=Brelan[0];
    }
    else if(Db_Pair.valide)
    {
        nb_Combi_Joueur1=2; Combi_Joueur1=Db_Pair;
    }
    else if(Pair[0].valide)
    {
        nb_Combi_Joueur1=1; Combi_Joueur1=Pair[0];
    }
    else nb_Combi_Joueur1=0;
  }
  else
  {
    if(Quinte_flush_royal.valide)
    {
       nb_Combi_Joueur2=9; Combi_Joueur2=Quinte_flush_royal;
    }
    else if(Quinte_flush.valide)
    {
        nb_Combi_Joueur2=8; Combi_Joueur2=Quinte_flush;
    }
    else if(Carre.valide)
    {
        nb_Combi_Joueur2=7; Combi_Joueur2=Carre;
    }
    else if(Full_house.valide)
    {
        nb_Combi_Joueur2=6; Combi_Joueur2=Full_house;
    }
    else if(Couleur.valide)
    {
        nb_Combi_Joueur2=5; Combi_Joueur2=Couleur;
        for(i=0;i<5;i++)
        {
           J2_Couleur[i]=Tab_Couleur[i];
        }
    }
    else if(Quinte.valide)
    {
        nb_Combi_Joueur2=4; Combi_Joueur2=Quinte;
    }
    else if(Brelan[0].valide)
    {
        nb_Combi_Joueur2=3; Combi_Joueur2=Brelan[0];
    }
    else if(Db_Pair.valide)
    {
        nb_Combi_Joueur2=2; Combi_Joueur2=Db_Pair;
    }
    else if(Pair[0].valide)
    {
        nb_Combi_Joueur2=1; Combi_Joueur2=Pair[0];
    }
    else nb_Combi_Joueur2=0;
  }
}

void Assigner_Gagnant() //Compare les meilleurs combinaisons des 2 joueurs et désigne le vainqueur
{
    if(nb_Combi_Joueur1<nb_Combi_Joueur2) Gagnant=2;
    else if(nb_Combi_Joueur1>nb_Combi_Joueur2) Gagnant=1;
    else
    {
        if(nb_Combi_Joueur1==9||nb_Combi_Joueur1==8||nb_Combi_Joueur1==4) // Si les 2 ont des Quintes...
            Double_Quinte();
        else if(nb_Combi_Joueur1==7||nb_Combi_Joueur1==3||nb_Combi_Joueur1==1)
            Double_Carre_Brelan_ou_Pair();
        else if(nb_Combi_Joueur1==0)
            Carte_La_Plus_Forte(7);
        else if(nb_Combi_Joueur1==2||nb_Combi_Joueur1==6)
            Double_FullHouse_DoublePair();
        else if(nb_Combi_Joueur1==5)
            Double_Couleur();

    }
}

void Double_Quinte() //Compare les 2 quintes pour trouver la plus forte
{
    if(Combi_Joueur1.valeur>Combi_Joueur2.valeur) Gagnant=1;
    else if(Combi_Joueur1.valeur<Combi_Joueur2.valeur) Gagnant=2;
    else
    {
        if(Joueur1[5].valeur>Combi_Joueur1.valeur) // Met les cartes de la quinte en dernier
        {
            Inverser_Cartes(&Joueur1[5],&Joueur1[0]);
            Inverser_Cartes(&Joueur1[6],&Joueur1[1]);
        }
        else if(Joueur1[6].valeur>Combi_Joueur1.valeur) Inverser_Cartes(&Joueur1[6],&Joueur1[1]);
        if(Joueur2[5].valeur>Combi_Joueur1.valeur) // Met les cartes de la quinte en dernier
        {
            Inverser_Cartes(&Joueur2[5],&Joueur2[0]);
            Inverser_Cartes(&Joueur2[6],&Joueur2[1]);
        }
        else if(Joueur2[6].valeur>Combi_Joueur1.valeur) Inverser_Cartes(&Joueur2[6],&Joueur2[1]);
        //maintenant les 2 cartes qui ne sont pas de la quinte sont les premieres
        if(Joueur1[1].valeur>Joueur2[1].valeur) Gagnant=1;
        else if(Joueur1[1].valeur<Joueur2[1].valeur) Gagnant=2;
        else
        {
            if(Joueur1[0].valeur>Joueur2[0].valeur) Gagnant=1;
            else if(Joueur1[0].valeur<Joueur2[0].valeur) Gagnant=2;
        }
    }
}

void Double_Carre_Brelan_ou_Pair() //Compare les 2 Pairs/Brelan/Carrés pour trouver la plus forte
{
    if(Combi_Joueur1.valeur>Combi_Joueur2.valeur) Gagnant=1;
    else if(Combi_Joueur1.valeur<Combi_Joueur2.valeur) Gagnant=2;
    else
    {
       if(nb_Combi_Joueur1==7) {Mettre_Combinaison_en_fin(4); Carte_La_Plus_Forte(3);}
       else if(nb_Combi_Joueur1==3) {Mettre_Combinaison_en_fin(3); Carte_La_Plus_Forte(4);}
       else if(nb_Combi_Joueur1==1) {Mettre_Combinaison_en_fin(2); Carte_La_Plus_Forte(5);}
    }
}

void Mettre_Combinaison_en_fin(int nbCartes) //Renvoi les carte de la combinaison aux derniers emplacement de la main
{
    int n=6-nbCartes, i, j;
    if(nbCartes==3&&(Joueur1[0].valeur==Combi_Joueur1.valeur)) Inverser_Cartes(&Joueur1[0],&Joueur1[3]);
    if(nbCartes==3&&(Joueur2[0].valeur==Combi_Joueur1.valeur)) Inverser_Cartes(&Joueur2[0],&Joueur2[3]);
    if(nbCartes==2)
    {
        if(Joueur1[0].valeur==Combi_Joueur1.valeur) Inverser_Cartes(&Joueur1[0],&Joueur1[2]);
        if(Joueur2[0].valeur==Combi_Joueur1.valeur) Inverser_Cartes(&Joueur2[0],&Joueur2[2]);
        for(i=1;i<=2;i++)
        {
            if(Joueur1[i].valeur==Combi_Joueur1.valeur) Inverser_Cartes(&Joueur1[i],&Joueur1[i+2]);
            if(Joueur2[i].valeur==Combi_Joueur1.valeur) Inverser_Cartes(&Joueur2[i],&Joueur2[i+2]);
        }
    }
    for(i=0;i<=n;i++)
       {
           if(Joueur1[i].valeur==Combi_Joueur1.valeur)
           {
               for(j=n+1;j<=6;j++)
               {
                   if(Joueur1[j].valeur!=Combi_Joueur1.valeur)
                   {
                       Inverser_Cartes(&Joueur1[i], &Joueur1[j]);
                       break;
                   }
               }
           }
           if(Joueur2[i].valeur==Combi_Joueur1.valeur)
           {
               for(j=n+1;j<=6;j++)
               {
                   if(Joueur2[j].valeur!=Combi_Joueur1.valeur)
                   {
                       Inverser_Cartes(&Joueur2[i], &Joueur2[j]);
                       break;
                   }
               }
           }
       }
}

void Carte_La_Plus_Forte(int nbCartes) //Fait un nombre(nbCartes) de comparaisons 2 à 2 des cartes des 2 mains ayant le meme emplacement
{
    int n=nbCartes-1, i;
    for(i=n;i>=0;i--)
    {
        if(Joueur1[i].valeur>Joueur2[i].valeur)
        {
            Gagnant=1; break;
        }
        else if(Joueur1[i].valeur<Joueur2[i].valeur)
        {
            Gagnant=2; break;
        }
    }
}

void Double_FullHouse_DoublePair() //Compare les 2 FullHouse/DoublePairs pour trouver la plus forte
{
    int n, i, j;
    if(Combi_Joueur1.valeur>Combi_Joueur2.valeur) Gagnant=1;
    else if(Combi_Joueur1.valeur<Combi_Joueur2.valeur) Gagnant=2;
    else
    {
        if(Combi_Joueur1.couleur>Combi_Joueur2.couleur) Gagnant=1;
        else if(Combi_Joueur1.couleur<Combi_Joueur2.couleur) Gagnant=2;
        else
        {
          if(nb_Combi_Joueur1==6)
          {
            n=min(Combi_Joueur1.valeur,Combi_Joueur1.couleur);
           for(i=0;i<=1;i++)
           {
             if(Joueur1[i].valeur==n)
             {
               for(j=2;j<=6;j++)
               {
                   if(Joueur1[j].valeur!=Combi_Joueur1.valeur&&Joueur1[j].valeur!=Combi_Joueur1.couleur)
                   {
                       Inverser_Cartes(&Joueur1[i], &Joueur1[j]);
                       break;
                   }
               }
             }
             if (Joueur2[i].valeur==n)
             {
               for(j=2;j<=6;j++)
               {
                   if(Joueur2[j].valeur!=Combi_Joueur1.valeur&&Joueur2[j].valeur!=Combi_Joueur2.couleur)
                   {
                       Inverser_Cartes(&Joueur2[i], &Joueur2[j]);
                       break;
                   }
               }
             }
           }
           Carte_La_Plus_Forte(2);
         }
         else if(nb_Combi_Joueur1==2)
         {
            if(Joueur1[0].valeur==Combi_Joueur1.valeur||Joueur1[0].valeur==Combi_Joueur1.couleur)
            {
               for(j=2;j<=6;j++)
               {
                   if(Joueur1[j].valeur!=Combi_Joueur1.valeur&&Joueur1[j].valeur!=Combi_Joueur1.couleur)
                   {
                       Inverser_Cartes(&Joueur1[0], &Joueur1[j]);
                       break;
                   }
               }
            }
            if(Joueur2[0].valeur==Combi_Joueur1.valeur||Joueur2[0].valeur==Combi_Joueur1.couleur)
            {
                for(j=2;j<=6;j++)
               {
                   if(Joueur2[j].valeur!=Combi_Joueur1.valeur&&Joueur2[j].valeur!=Combi_Joueur1.couleur)
                   {
                       Inverser_Cartes(&Joueur2[0], &Joueur2[j]);
                       break;
                   }
               }
            }
            for(i=0;i<=2;i++)
            {
             if(Joueur1[i].valeur==Combi_Joueur1.valeur||Joueur1[i].valeur==Combi_Joueur1.couleur)
             {
               for(j=3;j<=6;j++)
               {
                   if(Joueur1[j].valeur!=Combi_Joueur1.valeur&&Joueur1[j].valeur!=Combi_Joueur1.couleur)
                   {
                       Inverser_Cartes(&Joueur1[i], &Joueur1[j]);
                       break;
                   }
               }
             }
             if (Joueur2[i].valeur==Combi_Joueur1.valeur||Joueur2[i].valeur==Combi_Joueur1.couleur)
             {
               for(j=3;j<=6;j++)
               {
                   if(Joueur2[j].valeur!=Combi_Joueur1.valeur&&Joueur2[j].valeur!=Combi_Joueur1.couleur)
                   {
                       Inverser_Cartes(&Joueur2[i], &Joueur2[j]); printf("Boo\n");
                       break;
                   }
               }
             }
           }
           Carte_La_Plus_Forte(3);
        }
      }
   }
}

void Double_Couleur() //Compare les 2 Couleurs pour trouver la plus forte
{
   int i, j;
    for(i=4;i>=0;i--)
    {
        if(J1_Couleur[i].valeur>J2_Couleur[i].valeur)
        {
            Gagnant=1; break;
        }
        else if(J1_Couleur[i].valeur<J2_Couleur[i].valeur)
        {
            Gagnant=2; break;
        }
    }
    if(!Gagnant)
    {
       for(i=0;i<=1;i++)
       {
         if(Joueur1[i].valeur>=Combi_Joueur1.valeur&&Joueur1[i].couleur==Combi_Joueur1.couleur)
         {
            for(j=i+1;j<=6;j++)
            {
                if(Joueur1[j].valeur<Combi_Joueur1.valeur||Joueur1[j].couleur!=Combi_Joueur1.couleur)
                {
                    Inverser_Cartes(&Joueur1[i], &Joueur1[j]);
                    break;
                }
            }
          }
          if(Joueur2[i].valeur>=Combi_Joueur2.valeur&&Joueur2[i].couleur==Combi_Joueur2.couleur)
          {
            for(j=i+1;j<=6;j++)
            {
                if(Joueur2[j].valeur<Combi_Joueur2.valeur||Joueur2[j].couleur!=Combi_Joueur2.couleur)
                {
                    Inverser_Cartes(&Joueur2[i], &Joueur2[j]);
                    break;
                }
            }
          }
      }
      Carte_La_Plus_Forte(2);
    }
}
void Lire_Combinaisons(int nbCombi, COMBINAISON Combi) //Affiche la valeur ou la couleur de la combinaison
{
   if(nbCombi==1) printf(" de %s",TabValeur[Combi.valeur]);
   else if(nbCombi==2) printf(" de %s et de %s",TabValeur[Combi.valeur], TabValeur[Combi.couleur]);
   else if(nbCombi==3) printf(" %s", TabValeur[Combi.valeur]);
   else if(nbCombi==5) printf(" %s", TabCouleur[Combi.couleur]);
   else if(nbCombi==6) printf(" %s a %s",TabValeur[Combi.valeur], TabValeur[Combi.couleur]);
   else if(nbCombi==7) printf(" de %s",TabValeur[Combi.valeur]);
   else if(nbCombi==8||nbCombi==9) printf(" a %s",TabCouleur[Combi.couleur]);
}
