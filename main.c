#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "struct.h"

typedef int bool;
#define DIMX 35
#define DIMY 23
void afficherImage ( int x ,int y ,SDL_Renderer* renderer ,char* nomFichier )
{
     SDL_Surface* surface_image = SDL_LoadBMP (nomFichier);

     if ( surface_image )
     {
         SDL_Texture* image = SDL_CreateTextureFromSurface ( renderer , surface_image );

         if ( image )
         {
             SDL_SetRenderTarget ( renderer , image );

             SDL_Rect r;
             r.x = x;
             r.y = y;

             SDL_QueryTexture ( image, NULL, NULL, &(r.w), &(r.h));

             //printf ("On rend l'image dans le rectangle %d %d %d %d\n", r.x, r.y, r.w, r.h);

             SDL_RenderCopy ( renderer , image , NULL , &r);
             SDL_SetRenderTarget ( renderer , NULL );
             SDL_DestroyTexture (image);
         }
         else {
            fprintf (stderr, "Erreur de création de la texture\n");
         }

         SDL_FreeSurface (surface_image);
     }
     else {
        fprintf (stderr, "Erreur de chargement de l'image %s\n", nomFichier);
     }
}

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


int main(int argc, char** argv)
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
 SDL_Event event;

     if ( SDL_Init (SDL_INIT_VIDEO) != 0 )
     {
         fprintf (stderr, "Erreur d'initialisation du mécanisme SDL : %s\n", SDL_GetError() );
         return EXIT_FAILURE;
     }
     SDL_Window* fenetre = SDL_CreateWindow ("Exemple 5" ,SDL_WINDOWPOS_UNDEFINED ,SDL_WINDOWPOS_UNDEFINED ,1280 ,720 ,SDL_WINDOW_SHOWN);

     if ( fenetre == NULL )
     {
         fprintf (stderr, "Erreur de création de la fenêtre : %s\n",SDL_GetError());
         return EXIT_FAILURE;
     }

     SDL_RendererInfo info;

     int nbDrivers = SDL_GetNumRenderDrivers ();
     for ( int i=0; i<nbDrivers; i++)
     {
         SDL_GetRenderDriverInfo ( i, &info );

         printf ("Driver numero %d : \n", i);
         printf (" - name : %s \n", info.name);
         printf (" - flags : ");

         if ( info.flags & SDL_RENDERER_SOFTWARE ) printf ("SDL_RENDERER_SOFTWARE ");
         if ( info.flags & SDL_RENDERER_ACCELERATED ) printf ("SDL_RENDERER_ACCELERATED ");
         if ( info.flags & SDL_RENDERER_PRESENTVSYNC ) printf ("SDL_RENDERER_PRESENTVSYNC ");
         if ( info.flags & SDL_RENDERER_TARGETTEXTURE) printf ("SDL_RENDERER_TARGETTEXTURE ");
         printf ("\n");
     }

     SDL_Renderer* renderer = SDL_CreateRenderer ( fenetre, -1, SDL_RENDERER_ACCELERATED);







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

    for (int i = 0; i <= numLab; i++)
    {
        for ( int y = 0 ; y < DIMY; y++ )
        {
            for ( int x = 0 ; x < DIMX; x++ )
            {
                                if ( x == joueur.x && y == joueur.y )
            {
                afficherImage ( x*16, y*16, renderer , "img/joueur.bmp");
            }
            else
            {
                switch (labyrinthe[i][y][x])
                {
                    case  'C' : afficherImage ( x*16, y*16, renderer , "img/key.bmp");break;
                    case  'S' : if (cle == 1)
                                {
                                    afficherImage ( x*16, y*16, renderer , "img/porteO.bmp");break;
                                }
                                else
                                {
                                    afficherImage ( x*16, y*16, renderer , "img/porteF.bmp");break;
                                }
                                break;
                    case  ',' :
                        switch (i)
                        {
                            case 0 :afficherImage ( x*16, y*16, renderer , "img/coin.bmp");break;
                            case 1 :afficherImage ( x*16, y*16, renderer , "img/coin2.bmp");break;
                            case 2 :afficherImage ( x*16, y*16, renderer , "img/coin2.bmp");break;
                        }
                        break;
                    case  'J' : printf (" "); break;
                    case  '*' : afficherImage ( x*16, y*16, renderer , "img/pic.bmp");break;
                    case  '#' :
                        switch (i)
                        {
                            case 0 : afficherImage ( x*16, y*16, renderer , "img/mur.bmp");break;
                            case 1 : afficherImage ( x*16, y*16, renderer , "img/mur2.bmp");break;
                            case 2 : afficherImage ( x*16, y*16, renderer , "img/mur2.bmp");break;
                        }
                        break;
                    case  '.' :
                        switch (i)
                        {
                            case 0 :afficherImage ( x*16, y*16, renderer , "img/point.bmp");break;
                            case 1 :afficherImage ( x*16, y*16, renderer , "img/point2.bmp");break;
                            case 2 :afficherImage ( x*16, y*16, renderer , "img/point2.bmp");break;
                        }
                        break;
                    case  ' ' :break;
                    case  'P' :break;
                    case  'E' : afficherImage ( x*16, y*16, renderer , "img/ennemi.bmp");break;
                    case  't' : printf ("♫"); break;

                    case  'o' :
                                if (change == FALSE)
                                {
                                    afficherImage ( x*16, y*16, renderer , "img/piegeF.bmp");break;
                                    break;
                                }
                                else if (change == TRUE)
                                {
                                    afficherImage ( x*16, y*16, renderer , "img/piegeO.bmp");break;
                                    break;
                                }break;
                }
            }

            }

          printf ("\n");
        }
        do
        {

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

        SDL_RenderPresent(renderer);

        SDL_PollEvent (&event);
            switch ( event.type )
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_z : if ( labyrinthe[numLab][joueur.y-1][joueur.x   ] != '#' || labyrinthe[numLab][joueur.y-1][joueur.x   ] != 'o')
                                {
                                    while (labyrinthe[numLab][joueur.y-1][joueur.x] != '#' && labyrinthe[numLab][joueur.y-1][joueur.x   ] != 'o')
                                    {
                                        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/sol.bmp");
                                        joueur.y--;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/joueur.bmp");

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

                        case SDLK_q : if ( labyrinthe[numLab][joueur.y  ][joueur.x -1] != '#' || labyrinthe[numLab][joueur.y][joueur.x-1] != 'o')
                                {
                                    while (labyrinthe[numLab][joueur.y][joueur.x-1] != '#' && labyrinthe[numLab][joueur.y][joueur.x-1] != 'o')
                                    {
                                        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/sol.bmp");
                                        joueur.x--;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/joueur.bmp");

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

                        case SDLK_d : if ( labyrinthe[numLab][joueur.y  ][joueur.x +1] != '#' || labyrinthe[numLab][joueur.y][joueur.x+1] != 'o')
                                {
                                    while (labyrinthe[numLab][joueur.y][joueur.x+1] != '#' && labyrinthe[numLab][joueur.y][joueur.x+1] != 'o')
                                    {
                                        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/sol.bmp");
                                        joueur.x++;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/joueur.bmp");

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

                        case SDLK_s : if ( labyrinthe[numLab][joueur.y+1][joueur.x   ] != '#' || labyrinthe[numLab][joueur.y+1][joueur.x   ] != 'o')
                                {
                                    while (labyrinthe[numLab][joueur.y+1][joueur.x] != '#' && labyrinthe[numLab][joueur.y+1][joueur.x   ] != 'o')
                                    {
                                        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/sol.bmp");
                                        joueur.y++;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        afficherImage ( joueur.x*16, joueur.y*16, renderer , "img/joueur.bmp");

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
                        case SDLK_ESCAPE: touche = 8; break;
                    }
            }



            if (labyrinthe[numLab][joueur.y][joueur.x]=='S')
            {
                if (cle == 1)
                {
                    joueur.x = porte[1].x;
                    joueur.y = porte[1].y;
                    numLab = 1;
                    touche = 8;
                }
                else printf("Il faut posséder la clé !!");
            }

        if(numLab == 1)
        {
            for (int e = 0; e < 4; e++)
            {
                switch (deplacementMob[i])
                {
                    case 0 : if (labyrinthe[numLab][ennemies[e].y-1][ennemies[e].x] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                ennemies[e].y--;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                            }
                            else deplacementMob[i] = 1;
                            break;

                    case 1 : if (labyrinthe[numLab][ennemies[e].y+1][ennemies[e].x] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                ennemies[e].y++;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                            }
                            else deplacementMob[i] = 0;
                            break;

                    case 2 : if (labyrinthe[numLab][ennemies[i].y][ennemies[i].x-1] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                ennemies[e].x--;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                            }
                            else deplacementMob[e] = 3;
                            break;

                    case 3 : if (labyrinthe[numLab][ennemies[e].y][ennemies[e].x+1] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                ennemies[e].x++;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                            }
                            else deplacementMob[e] = 2;
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
            if (numLab == 1)
            {
                cle = 0;
            }


        }
        while (touche !=8);
        SDL_RenderClear (renderer);
        touche = 0;
    }

     SDL_DestroyRenderer (renderer);
     SDL_DestroyWindow (fenetre);
     SDL_Quit ();
 return EXIT_SUCCESS;
 }
