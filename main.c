#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "struct.h"

#define DIMX 35
#define DIMY 23

void cookie (char labyrinthe[2][DIMY][DIMX+1], Coordonnees joueur, int* score, int *cle, int numLab, int* touche)
{

    if (labyrinthe[numLab][joueur.y][joueur.x]=='*')
    {
        printf ("Perdu, vous avez foncé sur un pic !\n");
        *touche = 8;
    }

    if (labyrinthe[numLab][joueur.y][joueur.x]=='.')
    {
        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
        *score += 100;
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
                                          "              #...................#" ,
                                          "              #        ********** #" ,
                                          "              #   J    *        * #" ,
                                          "              ##########       ## #" ,
                                          "                               #  #" ,
                                          "                               * ##" ,
                                          "                         ******* # " ,
                                          "                         #       # " ,
                                          "                         # ####### " ,
                                          "                        ## #       " ,
                                          "                        #  #       " ,
                                          "                        # ##       " ,
                                          "       ########  #####  # ######## " ,
                                          "  ######      ####   ####........# " ,
                                          "  #.........#      #     ..#####.# " ,
                                          "  #.######################.     .# " ,
                                          "  #.#                    *C......# " ,
                                          "  #.#                    ######### " ,
                                          "  #.#                              " ,
                                          "  #.#                              " ,
                                          "  #S#                              " ,
                                          "  ###                              " ,
                                        },

                                        {
                                          "####################" ,
                                          "#S......#          #" ,
                                          "# ##....# ######## #" ,
                                          "# ##...## ######## #" ,
                                          "# #####       #### #" ,
                                          "# ####### P####### #" ,
                                          "# ################ #" ,
                                          "#..................#" ,
                                          "####################" ,
                                          }};

  Coordonnees joueur;
  Coordonnees porte [2];


  int score = 0;
  int numLab = 0;
  int cle = 0;
  int Tdebut = time(NULL);
  int fin = 0;



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
                case 'S' :  porte[numLab].x = x;
                            porte[numLab].y = y;
            }
        }
    }
}

  int touche;
  printf ("Au debut, xJoueur=%d et yJoueur=%d dans le premier labyrinthe\n", joueur.x, joueur.y);

  printf ("xPorte[0]=%d et yPorte[0]=%d dans le premier labyrinthe\n", porte[0].x, porte[0].y);
  printf ("xPorte[1]=%d et yPorte[1]=%d dans le second  labyrinthe\n", porte[1].x, porte[1].y);

do
{

    printf ("\nSCORE : %d - ", score);

    printf ("%s labyrinthe - ", ( numLab==0 ? "Premier" : "Second" ));

    printf ("Clé : %s\n\n", ( cle ? "OUI" : "NON" ));

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
                                }

                }
            }
        }

      printf ("\n");
    }

    printf ("\n");
    printf ("5 : vers le haut\n");
    printf ("1 : vers la gauche\n");
    printf ("3 : vers la droite\n");
    printf ("2 : vers le bas\n");
    printf ("8 : sortir du programme\n");
    printf ("\n");

    printf ("Votre choix : ");

    scanf ("%d", &touche);

    printf ("\n");

    switch ( touche )
    {
        case 5 : if ( labyrinthe[numLab][joueur.y-1][joueur.x   ] != '#' )
                {
                    while (labyrinthe[numLab][joueur.y-1][joueur.x] != '#')
                    {
                        joueur.y--;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                        if (touche == 8)
                        {
                            return 0;
                        }
                    }

                }break;

        case 1 : if ( labyrinthe[numLab][joueur.y  ][joueur.x -1] != '#' )
                {
                    while (labyrinthe[numLab][joueur.y][joueur.x-1] != '#')
                    {
                        joueur.x--;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                        if (touche == 8)
                        {
                            return 0;
                        }
                    }

                }break;

        case 3 : if ( labyrinthe[numLab][joueur.y  ][joueur.x +1] != '#' )
                {
                    while (labyrinthe[numLab][joueur.y][joueur.x+1] != '#')
                    {
                        joueur.x++;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                        if (touche == 8)
                        {
                            return 0;
                        }
                    }
                }
                break;

        case 2 : if ( labyrinthe[numLab][joueur.y+1][joueur.x   ] != '#' )
                {
                    while (labyrinthe[numLab][joueur.y+1][joueur.x] != '#')
                    {
                        joueur.y++;
                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
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
            switch (numLab)
            {
                case 0 : joueur.x = porte[1].x;
                         joueur.y = porte[1].y;
                         numLab = 1;
                         break;

                case 1 : joueur.x = porte[0].x;
                         joueur.y = porte[0].y;
                         numLab = 0;
            }
        }
    }

    if (labyrinthe[numLab][joueur.y][joueur.x]=='P')
    {
        fin = 1;
    }

    int Tfin = time(NULL);
    int secondes = Tfin - Tdebut;

    if (fin == 1)
    {
        printf("Vous avez mis %d s à terminer le niveau, Bravo !\n", secondes);
        touche = 8;
    }
}
while ( touche != 8 );

    printf ("On quitte le programme...\n");
    return 0;
 }
