#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "Jeu.h"



extern CARTE Joueur1[7],Joueur2[7],Milieu[5], Jeu[52];
extern int gMax, Compte_final;
char *TabValeur[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *TabCouleur[] = {"Trefle", "Pique", "Carreau", "Coeur"};
extern signed char Nom_J1[15], Nom_J2[15];

void LIRE_NOMS() //Recupérer les noms des 2 joueurs
{
    cadre(30,100,8,14,15,0);
    gotoxy(35,10);
     printf("Joueur 1 entrez votre Pseudo : "); scanf("%[^\n]", &Nom_J1);
     getchar();
     gotoxy(35,12);
     printf("Joueur 2 entrez votre Pseudo : "); scanf("%[^\n]", &Nom_J2);
}

void InitJeu() // Initialisation du paquet de cartes. 52 cartes dans un ordre précis
{
int val, coul, i; i = 0;
 for (coul=0; coul<=3; coul++) //Alant de la 1ere à la 4eme couleur
 {
   for (val=0; val<13; val++) //Affecter 13 valeurs différentes par couleur de carte
   {
    Jeu[i].valeur = val;
    Jeu[i].couleur = coul;
    i++;
   }
 }
}

CARTE *Distribue(CARTE *pCarte) //Tire une carte aléatoirement dans le paquet sans répétition
{
 int indice;

 if (gMax)
 indice = rand()%(gMax); // gMax vaut 51 au départ, puis 50, 49, ...
 else
 indice = 0;
 // on renseigne la carte choisie, prise au hasard
 *pCarte = Jeu[indice];
 // On insère la dernière carte du paquet à la place !!!
 Jeu[indice] = Jeu[gMax];
 // une carte de moins dans le paquet
 gMax--;
 return pCarte;
}

void Affectation_Cartes() //Distribue les cartes tirés aux joueurs et sur la table
{
   int i;
   for (i=0; i<2; i++) //Affecte duex cartes à chaque joueur
   {
     Distribue(&Joueur1[i]);
     Distribue(&Joueur2[i]);
   }

   for(i=0; i<5; i++)//Affecte 5 cartes à la table qui seront retournées/revélées au fur et à mesure.
    {
        Distribue(&Milieu[i]);
    }
    for(i=2;i<7;i++) //Affectes les cartes de la table aux emplacement suivants des mains des joueurs
    {
        Joueur1[i]=Milieu[i-2];
        Joueur2[i]=Milieu[i-2];
    }
}

void Afficher_Cartes() //Affiche les cartes de chaque joueur dans leurs emplacements respectives

{
    int i;
    for(i=0;i<2;i++)
    {
        gotoxy(21,19+i); Joueur1[i].couleur<2?color(0,2):color(4,2); //Vérifie la couleur (Noir ou rouge) de la carte pour choisir la couleur d'affichage
        printf("[%s %s]", TabValeur[Joueur1[i].valeur], TabCouleur[Joueur1[i].couleur]); //Affiche la carte à son emplacement
        Joueur2[i].couleur<2?color(0,2):color(4,2); //Vérifie la couleur (Noir ou rouge) de la carte pour choisir la couleur d'affichage
        gotoxy(98,19+i); printf("[%s %s]", TabValeur[Joueur2[i].valeur], TabCouleur[Joueur2[i].couleur]); //Affiche la carte à son emplacement
    }
}
void Lire_Cartes(int n,CARTE card1[7])
{
    int i;
     for(i=0;i<n;i++)
     {
       card1[i].couleur<2?color(0,2):color(4,2); //Vérifie la couleur (Noir ou rouge) de la carte pour choisir la couleur d'affichage
       printf("[%s %s] ", TabValeur[card1[i].valeur], TabCouleur[card1[i].couleur]); //Affiche la carte
     }
}

 void Retourner_Cartes_Milieu(int i) //Affiche une ou plusieurs cartes du millieu selon le tour de mise
 {
     int j;
     Nettoyer_cadre(1,125,10,10,2); gotoxy(50,10); color(1,0); //Nettoie l'emplacement de la notification quand les cartes sont retournés
     if(i==1) // Si on est au 1er tour de mise...
     {
        printf("3 cartes ont ete retournes sur la table");
       for(j=0;j<=2;j++)  //Affiche les 3 premières cartes à leurs emplacements dans le cadre
       {
        gotoxy(60,19+j); Milieu[j].couleur<2?color(0,2):color(4,2);
        printf("[%s %s]", TabValeur[Milieu[j].valeur], TabCouleur[Milieu[j].couleur]);
       }
     }
     else if(i==2) // Si on est au 2eme tour de mise...
     {
          //Affiche la 4eme carte à son emplacement dans le cadre
         printf("Une autre cartes da ete retourne sur la table");
         gotoxy(60,22); Milieu[3].couleur<2?color(0,2):color(4,2);
         printf("[%s %s]", TabValeur[Milieu[3].valeur], TabCouleur[Milieu[3].couleur]);
     }
     else if(i==3) // Si on est au 3eme tour de mise...
     {
         //Affiche la 5eme carte à son emplacement dans le cadre
         printf("Une derniere carte a ete retourne sur la table");
         gotoxy(60,23); Milieu[4].couleur<2?color(0,2):color(4,2);
         printf("[%s %s]", TabValeur[Milieu[4].valeur], TabCouleur[Milieu[4].couleur]);
     }
     gotoxy(47,35); system("pause"); Nettoyer_cadre(40,95,35,35,2); Nettoyer_cadre(1,125,10,10,2); //Mettre pause puis néttoyer l'emplacement des notifications
 }
void Inverser_Cartes(CARTE *Card1, CARTE *Card2) //Echange la position de 2 cartes dans une main(tableau de cartes) en utilisant leurs adresses mémoire
{
    CARTE Temporaire; //une carte temporaire
    Temporaire=*Card1;
    *Card1=*Card2;
    *Card2=Temporaire;
}

void Type_de_partie() //Permet de choisir un des types de partie
{
    int choix;
    ligne_Horizontale(30,100,21,15,0);
    cadre(30,100,17,25,15,0); //Cadre plus la ligne trace un tableau
    gotoxy(50,18); printf("Choisissez un type de partie"); gotoxy(40,19); printf("1. Partie Absolu (Jusqu'a faucher l'adversaire)");
    gotoxy(40,20); printf("2. Parrtie en nombre de manches predefini");
    do
    {
        Nettoyer_cadre(31,99,22,22,0); // Nettoie l'emplacement de la notification
        gotoxy(50,22); printf("Entrez votre choix : "); scanf("%d",&choix);
        gotoxy(45,24);
        if(choix<1||choix>2) printf("Erreur, entrez une valeur valide");
    }
    while(choix<1||choix>2); //jusqu'a ce que le choix soit valide
    if(choix==1) Compte_final=1000;
    else if(choix==2)
    {
        cadre(30,100,27,30,15,0);
        do
        {
          Nettoyer_cadre(31,99,28,28,0); gotoxy(40,28);
          printf("Entrez le nombre de manches (au moin 2) : "); scanf("%d",&Compte_final);
          gotoxy(40,29);
          if(Compte_final<2) printf("Trop petit. Entrez plus de manches");
        }
        while(Compte_final<2); //pour joueur au moins 2 manches
    }
}

void color(int couleurDuTexte,int couleurDeFond) //texte qui suit en couleur Texte et de de couleur de font Fond
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void gotoxy(int x, int y) //Met le curseur au point de coordonées (x,y) pour entrer des valeurs ou afficher

{
   HANDLE hConsoleOutput;
   COORD dwCursorPosition;
   //cout.flush();
   dwCursorPosition.X = x;
   dwCursorPosition.Y = y;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void cadre(int x1,int x2,int y1,int y2,int cfg, int cbg) //trace un cadre carré de x1 à x2 sur l'horizontale et de y1 à y2 sur la verticale de couleur cfg et couleur de fond cbg
{
    int i;
    color(cfg,cbg);
    for(i=x1;i<=x2;i++) //trace les 2 horizontaies du cadre
    {
        gotoxy(i,y1);
        printf("%c", 205);
        gotoxy(i,y2);
        printf("%c", 205);
    }
    for(i=y1;i<=y2;i++) //trace les 2 verticales du cadre
    {
        gotoxy(x1,i);
        printf("%c", 186);
        gotoxy(x2,i);
        printf("%c", 186);
    }
    //Corige les bordures du cadre
   gotoxy(x1,y1);printf("%c", 201);
    gotoxy(x2,y1);printf("%c", 187);
    gotoxy(x1,y2);printf("%c", 200);
    gotoxy(x2,y2);printf("%c", 188);
}
void ligne_Horizontale(int x1, int x2, int y, int c, int b) //trace une ligne horizontale de x1+1 à x2-1 de couleur c et zrriere-plan b
{
    cadre(x1,x2,y,y,c,b); color(c,b); //Un cadre aux 2 horizontales confondues
    gotoxy(x1,y); printf(" ");
    gotoxy(x2,y); printf(" ");
    //Les 2 dernieres instruction corrigent les extremités de la ligne
}

void ligne_Verticale(int x, int y1, int y2, int c, int b) //trace une ligne verticale de y1+1 à y2-1 de couleur c et zrriere-plan b
{
    cadre(x,x,y1,y2,c,b); color(c,b); //Un cadre aux 2 verticales confondues
    gotoxy(x,y1); printf(" ");
    gotoxy(x,y2); printf(" ");
    //Les 2 dernieres instruction corrigent les extremités de la ligne
}

void Nettoyer_cadre(int x1, int x2, int y1, int y2, int bgc) //Permet de repeindre une selection de une couleur donnée
{
    int y, x;
    color(15,bgc);
    for(y=y1;y<=y2;y++)
    {
        for(x=x1;x<=x2;x++)
        {
           gotoxy(x,y); printf(" ");
        }
    }
}

void menu(int c,int bgc) // Affiche le titre du jeu en des couleurs spécifiés
{
    Nettoyer_cadre(50,80,2,5,bgc);
    ligne_Horizontale(50,80,2,c,bgc);
    cadre(50,80,5,5,c,bgc);
    gotoxy(56,3); printf("TEXAS HOLDEM POKER");
    gotoxy(58,4); printf("By Miky And Co.");
}

void Afficher_Cadres() // Affiche tous les cadres/boxes avec leurs contenus statiques
{
    system("cls");
    system("cmd /c \"color 2f\""); //Vider l'écran puis le repeindre en vert (fonction exclusive du systeme windows)
    menu(1,0);
    cadre(55,67,7,9,15,2); gotoxy(57,8); printf("MANCHE No");
    cadre(67,74,7,9,15,2); //Valeur manche gotoxy(70,8); printf("1234");
    cadre(50,60,11,13,15,2); gotoxy(53,12); printf("POT");
    cadre(60,80,11,13,15,2); // valeur pot gotoxy(68,12); printf("1234");
    cadre(10,30,7,9,15,2); gotoxy(13,8); printf("BOURSE %s",Nom_J1);
    cadre(30,40,7,9,15,2); //valeur Bourse 1 gotoxy(33,8)
    cadre(90,110,7,9,15,2); gotoxy(93,8); printf("BOURSE %s",Nom_J2);
    cadre(110,120,7,9,15,2); //valeur Bourse 2 gotoxy(113,8)
    ligne_Horizontale(50,80,17,15,2);
    cadre(50,80,15,25,15,2); gotoxy(58,16); printf("CARTES TABLE"); //valeur carte milieu gotoxy(58,19-23)
    cadre(50,70,27,29,15,2); gotoxy(53,28); printf("TOUR DE MISE");
    cadre(70,80,27,29,15,2); //valeur tour de mise gotoxy(74,28)
    cadre(8,30,11,14,15,2); gotoxy(12,12); color(14,2); printf("%s",Nom_J1);
    cadre(30,45,11,14,15,2); gotoxy(35,12); printf("MISE"); //valeur mise 1 gotoxy(35,13)
    cadre(85,107,11,14,15,2); gotoxy(89,12); color(14,2); printf("%s",Nom_J2);
    cadre(107,122,11,14,15,2); gotoxy(112,12); printf("MISE"); //valeur mise 2 gotoxy(112,13)
    ligne_Horizontale(13,39,18,15,2);
    cadre(13,39,16,22,15,2); gotoxy(20,17); printf("CARTES %s",Nom_J1); //valeur carte joueur1 gotoxy(21,19-20)
    ligne_Horizontale(90,116,18,15,2);
    cadre(90,116,16,22,15,2); gotoxy(97,17); printf("CARTES %s",Nom_J2); //valeur carte joueur1 gotoxy(98,19-20)

    ligne_Verticale(18,26,29,15,2); ligne_Verticale(30,26,29,15,2);
    ligne_Horizontale(4,45,26,15,2); ligne_Horizontale(4,45,29,15,2); ligne_Horizontale(4,45,31,15,2);
    cadre(4,45,24,33,15,2);  //entrer question gotoxy(11,32)
    gotoxy(20,25); printf("ACTIONS");  //entrer information gotoxy(6,30)
    color(15,0); gotoxy(12,27); printf("1"); gotoxy(23,27);  printf("2"); gotoxy(36,27);  printf("3");
    gotoxy(10,28); printf("MISER"); gotoxy(21,28);  printf("CHECK"); gotoxy(32,28);  printf("SE COUCHER");

    ligne_Verticale(99,26,29,15,2); ligne_Verticale(111,26,29,15,2);
    ligne_Horizontale(85,126,26,15,2); ligne_Horizontale(85,126,29,15,2); ligne_Horizontale(85,126,31,15,2);
    cadre(85,126,24,33,15,2);  //entrer question gotoxy(92,32)
    gotoxy(101,25); printf("ACTIONS");  //entrer information gotoxy(87,30)
    color(15,0); gotoxy(93,27); printf("1"); gotoxy(104,27);  printf("2"); gotoxy(117,27);  printf("3");
    gotoxy(91,28); printf("MISER"); gotoxy(102,28);  printf("CHECK"); gotoxy(113,28);  printf("SE COUCHER");
}
