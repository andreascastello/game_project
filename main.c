#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "struct.h"

typedef int bool;
#define DIMX 35
#define DIMY 23

void cookie (char labyrinthe[2][DIMY][DIMX+1], Coordonnees joueur, int* score, int *cle, int numLab, int* touche)
{

    if (labyrinthe[numLab][joueur.y][joueur.x]=='*')
    {
        printf ("Perdu, vous avez foncé sur un pic !\n");
        *touche = 8;
    }
/* //marche pas quand c'est dans la fonction
    if (labyrinthe[numLab][joueur.y][joueur.x]=='o' && change == TRUE)
    {
        printf ("Perdu, vous avez foncé sur un mur piege !\n");
        *touche = 8;
    }
*/
    if (labyrinthe[numLab][joueur.y][joueur.x]=='E')
    {
        printf ("Perdu, vous avez foncé sur ennemi !\n");
        *touche = 8;
    }

    if (labyrinthe[numLab][joueur.y][joueur.x]=='.')
    {
        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
    }

    if (labyrinthe[numLab][joueur.y][joueur.x]==',')
    {
        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
        *score += 100;
    }

    if (labyrinthe[numLab][joueur.y][joueur.x]=='t')
    {
        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
        *score += 1000;
    }

    if (labyrinthe[numLab][joueur.y][joueur.x]=='C')
    {
        labyrinthe[numLab][joueur.y][joueur.x] =' ';
        *cle = 1;
    }
}


int main()
 {
  if (!SetConsoleOutputCP(65001))
   printf ("ERREUR\n");

  char labyrinthe [2][DIMY][DIMX+1]  = {{ "              #####################" ,
                                          "              #,..................#" ,
                                          "              #        **********.#" ,
                                          "              #   J    *        *.#" ,
                                          "              ##########       ##.#" ,
                                          "                               #..#" ,
                                          "                               *.##" ,
                                          "                         *******.# " ,
                                          "                         #......,# " ,
                                          "                         #.####### " ,
                                          "                        ##.#       " ,
                                          "                        #..#       " ,
                                          "                        #,##       " ,
                                          "       ########  #####  #.######## " ,
                                          "  ######......####...####.......,# " ,
                                          "  #........,#..,...#..,....#####,# " ,
                                          "  #.######################.     ,# " ,
                                          "  #.#                    *C.....,# " ,
                                          "  #.#                    ######### " ,
                                          "  #.#                              " ,
                                          "  #.#                              " ,
                                          "  #S#                              " ,
                                          "  ###                              " ,
                                        },

                                        {
                                          "                #########   " ,
                                          "                #P.....,#   " ,
                                          "                #######.#   " ,
                                          "                      #.#   " ,
                                          "      ###  #########  #.#   " ,
                                          "      #E#  #....,..####.#   " ,
                                          "   #### ####.##### E   .#   " ,
                                          "   #......##.#   #.####.#   " ,
                                          "   #.## #.  .#####.####.#   " ,
                                          "   #.####.##,...##......#   " ,
                                          "   #...##.   ##.#######,#   " ,
                                          "   ###.##,....,.#     ###   " ,
                                          "#### #.#####t####***********" ,
                                          "#.....,##E##o####*         *" ,
                                          "#.## #### ##.....*    ##   *" ,
                                          "#.## ##...,...##.......S   *" ,
                                          "#...,...# #.....,#         *" ,
                                          "####E#### #######*         *" ,
                                          "   ###  ###      #ooooooooo#" ,
                                          }};

  Coordonnees joueur;
  Coordonnees porte [2];
  Coordonnees ennemies [4];

  int score = 0;
  int numLab = 0;
  int cle = 0;
  int Tdebut = time(NULL);
  int fin = 0;

int nbMob = 0;

    for (int numLab = 0; numLab < 2; numLab++)
    {
        for ( int y = 0 ; y < DIMY; y++ )
        {
            for ( int x = 0 ; x < DIMX; x++ )
            {
                switch (labyrinthe[numLab][y][x])
                {
                    case 'J' :  joueur.x = x;
                                joueur.y = y;
                                break;
                    case 'E' :  ennemies[nbMob].x = x;
                                ennemies[nbMob].y = y;
                                nbMob++;
                                break;
                    case 'S' :  porte[numLab].x = x;
                                porte[numLab].y = y;
                }
            }
        }
    }


  int touche;
  int deplacementMob [4] = {0,2,0,1};

  bool change;
do
{
    system("cls");

    int Tfin = time(NULL);
    int secondes = Tfin - Tdebut;

    if (secondes % 2 == 0)
    {
        change = TRUE;
    }
    else change = FALSE;

    printf ("\nSCORE : %d - ", score);
    printf ("%s labyrinthe - ", ( numLab==0 ? "Premier" : "Second" ));
    printf ("Clé : %s\n\n", ( cle ? "OUI" : "NON" ));
    printf ("Temps écoulé  : %d s\n", secondes);

    for ( int y = 0 ; y < DIMY; y++ )
    {
        for ( int x = 0 ; x < DIMX; x++ )
        {
            if ( x == joueur.x && y == joueur.y )
            {
                printf ("☺");
            }
            else
            {
                switch (labyrinthe[numLab][y][x])
                {
                    case  '#' : if (y == 0)
                                {
                                    printf("▄");
                                    break;
                                }
                                else if (y == DIMY - 1)
                                {
                                    printf("▀");
                                    break;
                                }
                                else
                                {
                                                 printf ("█"); break;
                                     case  '.' : printf ("."); break;
                                     case  ' ' :
                                     case  'J' : printf (" "); break;
                                     case  'S' : printf ("¦"); break;
                                     case  'C' : printf ("©"); break;
                                     case  '*' : printf ("▒"); break;
                                     case  'P' : printf ("P"); break;
                                     case  'E' : printf ("☻"); break;
                                     case  ',' : printf ("▪"); break;
                                     case  't' : printf ("♫"); break;

                                }
                    case  'o' :
                                if (change == FALSE)
                                {
                                    printf ("▬");
                                    break;
                                }
                                else if (change == TRUE)
                                {
                                    printf ("▲");
                                    break;
                                }
                }
            }
        }

      printf ("\n");
    }

    printf ("  ↑\n");
    printf ("← ");
    printf ("↓ ");
    printf ("→ ");
    printf ("\n");
    printf ("-----\n");
    printf ("  z\n");
    printf ("q ");
    printf ("s ");
    printf ("d ");
    printf ("\n");

    printf ("Votre choix : \n");

        if(kbhit())
        {
            touche=getch();
        }
        else
        {
            touche = ' ';
        }
    switch ( touche )
    {
        case 'z' : if ( labyrinthe[numLab][joueur.y-1][joueur.x   ] != '#' || labyrinthe[numLab][joueur.y-1][joueur.x   ] != 'o')
                {
                    while (labyrinthe[numLab][joueur.y-1][joueur.x] != '#' && labyrinthe[numLab][joueur.y-1][joueur.x   ] != 'o')
                    {
                        joueur.y--;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);

                        if (labyrinthe[numLab][joueur.y-1][joueur.x   ] == 'o' && change == TRUE)
                        {
                            printf ("Perdu, vous avez foncé sur un mur piege !\n");
                            touche = 8;
                        }
                        if (touche == 8)
                        {
                            return 0;
                        }
                    }

                }break;

        case 'q' : if ( labyrinthe[numLab][joueur.y  ][joueur.x -1] != '#' || labyrinthe[numLab][joueur.y][joueur.x-1] != 'o')
                {
                    while (labyrinthe[numLab][joueur.y][joueur.x-1] != '#' && labyrinthe[numLab][joueur.y][joueur.x-1] != 'o')
                    {
                        joueur.x--;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                        if (labyrinthe[numLab][joueur.y][joueur.x-1] == 'o' && change == TRUE)
                        {
                            printf ("Perdu, vous avez foncé sur un mur piege !\n");
                            touche = 8;
                        }
                        if (touche == 8)
                        {
                            return 0;
                        }
                    }

                }break;

        case 'd' : if ( labyrinthe[numLab][joueur.y  ][joueur.x +1] != '#' || labyrinthe[numLab][joueur.y][joueur.x+1] != 'o')
                {
                    while (labyrinthe[numLab][joueur.y][joueur.x+1] != '#' && labyrinthe[numLab][joueur.y][joueur.x+1] != 'o')
                    {
                        joueur.x++;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                        if (labyrinthe[numLab][joueur.y][joueur.x+1] == 'o' && change == TRUE)
                        {
                            printf ("Perdu, vous avez foncé sur un mur piege !\n");
                            touche = 8;
                        }
                        if (touche == 8)
                        {
                            return 0;
                        }
                    }
                }
                break;

        case 's' : if ( labyrinthe[numLab][joueur.y+1][joueur.x   ] != '#' || labyrinthe[numLab][joueur.y+1][joueur.x   ] != 'o')
                {
                    while (labyrinthe[numLab][joueur.y+1][joueur.x] != '#' && labyrinthe[numLab][joueur.y+1][joueur.x   ] != 'o')
                    {
                        joueur.y++;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);

                        if (labyrinthe[numLab][joueur.y+1][joueur.x   ] == 'o' && change == TRUE)
                        {
                            printf ("Perdu, vous avez foncé sur un mur piege !\n");
                            touche = 8;
                        }
                        if (touche == 8)
                        {
                            return 0;
                        }
                    }
                }
                break;
    }



    if (labyrinthe[numLab][joueur.y][joueur.x]=='S')
    {
        if (cle == 1)
        {
            joueur.x = porte[1].x;
            joueur.y = porte[1].y;
            numLab = 1;
        }
        else printf("Il faut posséder la clé !!");
    }

if(numLab == 1)
{
    for (int i = 0; i < 4; i++)
    {
        switch (deplacementMob[i])
        {
            case 0 : if (labyrinthe[numLab][ennemies[i].y-1][ennemies[i].x] != '#')
                    {
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = ' ';
                        ennemies[i].y--;
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = 'E';
                    }
                    else deplacementMob[i] = 1;
                    break;

            case 1 : if (labyrinthe[numLab][ennemies[i].y+1][ennemies[i].x] != '#')
                    {
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = ' ';
                        ennemies[i].y++;
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = 'E';
                    }
                    else deplacementMob[i] = 0;
                    break;

            case 2 : if (labyrinthe[numLab][ennemies[i].y][ennemies[i].x-1] != '#')
                    {
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = ' ';
                        ennemies[i].x--;
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = 'E';
                    }
                    else deplacementMob[i] = 3;
                    break;

            case 3 : if (labyrinthe[numLab][ennemies[i].y][ennemies[i].x+1] != '#')
                    {
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = ' ';
                        ennemies[i].x++;
                        labyrinthe[numLab][ennemies[i].y][ennemies[i].x] = 'E';
                    }
                    else deplacementMob[i] = 2;
                    break;
        }
    }
}

    if (labyrinthe[numLab][joueur.y][joueur.x]=='P')
    {
        fin = 1;
    }

    if (fin == 1)
    {
        printf("Vous avez mis %d s à terminer le niveau, Bravo !\n", secondes);
        touche = 8;
    }

    Sleep(50);
}
while ( touche != 8 );

    printf ("On quitte le programme...\n");
    return 0;
 }
