#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "struct.h"

typedef int bool;
#define DIMX 35
#define DIMY 31
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
        switch (numLab)
        {
            case 0 : labyrinthe[0][21][3] = 's';break;
            case 1 : labyrinthe[1][2][17] = 's';break;
        }

    }
}


int main(int argc, char** argv)
 {
  if (!SetConsoleOutputCP(65001))
   printf ("ERREUR\n");

  char labyrinthe [3][DIMY][DIMX+1]  = {{ "              #####################" ,
                                          "              #,..................#" ,
                                          "              #________**********.#" ,
                                          "              #___J____*        *.#" ,
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
                                          "  #.######################._____,# " ,
                                          "  #.#                    *C.....,# " ,
                                          "  #.#                    ######### " ,
                                          "  #.#                              " ,
                                          "  #.#                              " ,
                                          "  #S#                              " ,
                                          "  ###                              " ,
                                        },

                                        {
                                          "                #########   " ,
                                          "                #......,#   " ,
                                          "                #S#####.#   " ,
                                          "                 #    #.#   " ,
                                          "      ###  #########  #.#   " ,
                                          "      #E#  #....,..####.#   " ,
                                          "   #### ####.##### E    #   " ,
                                          "   #......##.#___#.####.#   " ,
                                          "   #.## #.__.#####.####.#   " ,
                                          "   #.####.##C...##......#   " ,
                                          "   #...##.___##.#######,#   " ,
                                          "   ###.##,....,.#########   " ,
                                          "#### #.#####t####***********" ,
                                          "#... .,##E##o####*_________*" ,
                                          "#.## #### ##.....*____##___*" ,
                                          "#.## ##.. ,...##.......S___*" ,
                                          "#... ...# #.....,#_________*" ,
                                          "####E#### #######*_________*" ,
                                          "   ###  ###      #ooooooooo#" ,
                                          },

                                          {
                                          "     #         " ,
                                          "    #P#        " ,
                                          "    #.#        " ,
                                          "#####.#########" ,
                                          "*.....#_______*" ,
                                          "*,_______#____*" ,
                                          "*._#......____*" ,
                                          "*.__.##__.____*" ,
                                          "*.__.#....#___*" ,
                                          "#t...#._______*" ,
                                          "*___o#.____#__*" ,
                                          "*____#......__*" ,
                                          "*__________,__*" ,
                                          "*_______#__.__*" ,
                                          "***_____....o_*" ,
                                          "  *__#__.__.__*" ,
                                          "  *__....#_.__*" ,
                                          "  *__.__t__t__*" ,
                                          "  *__.__.#_#__*" ,
                                          "  *_#.....____*" ,
                                          "  #######.#####" ,
                                          "        #.###  " ,
                                          "#####   #...#  " ,
                                          "#...#######,###" ,
                                          "#.#.,...#.....#" ,
                                          "#.#####.#.*.#.#" ,
                                          "#.,...#.#...#.#" ,
                                          "#_____#,#####.#" ,
                                          "#_____#.......#" ,
                                          "#__S__#########" ,
                                          "#######        " ,
                                        }};

  Coordonnees joueur;
  Coordonnees porte [3];
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
     SDL_Window* fenetre = SDL_CreateWindow ("Exemple 5" ,SDL_WINDOWPOS_UNDEFINED ,SDL_WINDOWPOS_UNDEFINED ,1200 ,850 ,SDL_WINDOW_SHOWN);

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



SDL_RenderClear(renderer);



    for (int numLab = 0; numLab < 3; numLab++)
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
        switch (i)
        {
            case 0 :afficherImage ( 0, 0, renderer , "img/background2.bmp");break;
            case 1 :afficherImage ( 0, 0, renderer , "img/background.bmp");break;
            case 2 :afficherImage ( 0, 0, renderer , "img/background3.bmp");break;
        }
        for ( int y = 0 ; y < DIMY; y++ )
        {
            for ( int x = 0 ; x < DIMX; x++ )
            {

            if ( x == joueur.x && y == joueur.y )
            {
                switch (i)
                {
                case 0:
                    afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");
                    afficherImage ( x*25+100, y*25+100, renderer , "img/joueur.bmp");break;
                case 1:
                    afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                    afficherImage ( x*25+250, y*25+150, renderer , "img/joueur.bmp");break;
                case 2:
                    afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                    afficherImage ( x*25+400, y*25+30, renderer , "img/joueur.bmp");break;
                }

            }
            else
            {

                switch (labyrinthe[i][y][x])
                {

                    case  'C' : switch (i)
                    {
                        case 0:
                        afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");
                        afficherImage ( x*25+100, y*25+100, renderer , "img/key.bmp");break;
                        case 1:
                        afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                        afficherImage ( x*25+250, y*25+150, renderer , "img/key.bmp");break;
                    }break;

                    case  ',' :
                        switch (i)
                        {
                            case 0 :
                                afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");
                                afficherImage ( x*25+100, y*25+100, renderer , "img/coin.bmp");break;
                            case 1 :
                                afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                                afficherImage ( x*25+250, y*25+150, renderer , "img/coin2.bmp");break;
                            case 2 :
                                afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                                afficherImage ( x*25+400, y*25+30, renderer , "img/coin3.bmp");break;
                        }
                        break;

                    case  '*' : switch (i)
                    {
                        case 0:
                        afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");
                        afficherImage ( x*25+100, y*25+100, renderer , "img/pic.bmp");break;
                        case 1:
                        afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                        afficherImage ( x*25+250, y*25+150, renderer , "img/pic.bmp");break;
                        case 2:
                        afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                        afficherImage ( x*25+400, y*25+30, renderer , "img/pic.bmp");break;
                    }break;
                    case  '#' :
                        switch (i)
                        {
                            case 0 : afficherImage ( x*25+100, y*25+100, renderer , "img/mur.bmp");break;
                            case 1 : afficherImage ( x*25+250, y*25+150, renderer , "img/mur2.bmp");break;
                            case 2 : afficherImage ( x*25+400, y*25+30, renderer , "img/mur3.bmp");break;
                        }
                        break;
                    case  '.' :
                        switch (i)
                        {

                            case 0 :
                                afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");
                                afficherImage ( x*25+100, y*25+100, renderer , "img/point.bmp");break;
                            case 1 :
                                afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                                afficherImage ( x*25+250, y*25+150, renderer , "img/point2.bmp");break;
                            case 2 :
                                afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                                afficherImage ( x*25+400, y*25+30, renderer , "img/point3.bmp");break;
                        }
                        break;

                    case  'P' :
                        afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                        afficherImage ( x*25+400, y*25+30, renderer , "img/sortie.bmp");break;
                    case  'E' : switch(i)
                    {
                        case 1:
                            afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                            afficherImage ( x*25+250, y*25+150, renderer , "img/ennemi.bmp");break;
                        case 2:
                            afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                            afficherImage ( x*25+400, y*25+30, renderer , "img/ennemi.bmp");break;
                    }break;


                    case  't' :
                        switch (i)
                        {
                            case 1:
                                afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                                afficherImage ( x*25+250, y*25+150, renderer , "img/etoile.bmp");break;
                            case 2:
                                afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                                afficherImage ( x*25+400, y*25+30, renderer , "img/etoile.bmp");break;
                        }break;

                    case  ' ' :break;
                    case  '_' :
                        switch (i)
                            {
                                  case 0: afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");break;
                                  case 1: afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");break;
                                  case 2: afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");break;

                            }break;
                    case  's' :
                                switch (i)
                                {
                                    case 0 :
                                        afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");
                                        afficherImage ( x*25+100, y*25+100, renderer , "img/porteO.bmp");break;
                                    case 1 :
                                        afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                                        afficherImage ( x*25+250, y*25+150, renderer , "img/porteO.bmp");break;
                                    case 2 :
                                        afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                                        afficherImage ( x*25+400, y*25+30, renderer , "img/porteO.bmp");break;
                                }
                                break;

                    case  'S' : switch (i)
                                        {
                                            case 0 :
                                                afficherImage ( x*25+100, y*25+100, renderer , "img/sol.bmp");
                                                afficherImage ( x*25+100, y*25+100, renderer , "img/porteF.bmp");break;
                                            case 1 :
                                                afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                                                afficherImage ( x*25+250, y*25+150, renderer , "img/porteF.bmp");break;
                                            case 2 :
                                                afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                                                afficherImage ( x*25+400, y*25+30, renderer , "img/porteF.bmp");break;
                                        }
                                    break;
                    case  'o' :
                                    if (change == FALSE)
                                    {
                                        switch (i)
                                        {
                                            case 1 :
                                                afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                                                afficherImage ( x*25+250, y*25+150, renderer , "img/piegeF.bmp");break;
                                            case 2 :
                                                afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                                                afficherImage ( x*25+400, y*25+30, renderer , "img/piegeF.bmp");break;
                                        }
                                    }
                                    else if (change == TRUE)
                                    {

                                        switch (i)
                                        {
                                            case 1 :
                                                afficherImage ( x*25+250, y*25+150, renderer , "img/sol2.bmp");
                                                afficherImage ( x*25+250, y*25+150, renderer , "img/piegeO.bmp");break;
                                            case 2 :
                                                afficherImage ( x*25+400, y*25+30, renderer , "img/sol3.bmp");
                                                afficherImage ( x*25+400, y*25+30, renderer , "img/piegeO.bmp");break;
                                        }
                                    }break;


                }
            }

            }

          printf ("\n");
        }
            if (numLab == 1)
            {
                cle = 0;
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
            printf ("%s labyrinthe - ", ( numLab==0 ? "Premier" : "Second"));
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
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/sol.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/sol2.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/sol3.bmp");break;
                                        }
                                        joueur.y--;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/joueur.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/joueur.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/joueur.bmp");break;
                                        }
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
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/sol.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/sol2.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/sol3.bmp");break;
                                        }
                                        joueur.x--;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/joueur4.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/joueur4.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/joueur4.bmp");break;
                                        }

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
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/sol.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/sol2.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/sol3.bmp");break;
                                        }
                                        joueur.x++;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/joueur2.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/joueur2.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/joueur2.bmp");break;
                                        }

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
                                    while (labyrinthe[numLab][joueur.y+1][joueur.x] != '#' && labyrinthe[numLab][joueur.y+1][joueur.x   ] != 'o' && labyrinthe[numLab][joueur.y+1][joueur.x   ] != 'S')
                                    {
                                        labyrinthe[numLab][joueur.y][joueur.x] = ' ';
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/sol.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/sol2.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/sol3.bmp");break;
                                        }
                                        joueur.y++;
                                        cookie (labyrinthe, joueur, &score, &cle, numLab, &touche);
                                        switch (numLab)
                                        {
                                            case 0 :afficherImage ( joueur.x*25+100, joueur.y*25+100, renderer , "img/joueur3.bmp");break;
                                            case 1 :afficherImage ( joueur.x*25+250, joueur.y*25+150, renderer , "img/joueur3.bmp");break;
                                            case 2 :afficherImage ( joueur.x*25+400, joueur.y*25+30, renderer , "img/joueur3.bmp");break;
                                        }

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



            if (labyrinthe[numLab][joueur.y][joueur.x]=='s')
            {
                if (cle == 1)
                {
                    switch (numLab)
                    {
                        case 0 :
                                joueur.x = porte[1].x;
                                joueur.y = porte[1].y;
                                numLab = 1;
                                touche = 8;
                                break;
                        case 1 :
                                joueur.x = porte[2].x;
                                joueur.y = porte[2].y;
                                numLab = 2;
                                touche = 8;
                                break;
                    }

                }
            }
            else if (labyrinthe[numLab][joueur.y+1][joueur.x]=='S' && cle == 0)
            {
                printf("Il faut posséder la clé !!");
            }

        if(numLab == 1)
        {
            for (int e = 0; e < 4; e++)
            {
                switch (deplacementMob[e])
                {
                    case 0 : if (labyrinthe[numLab][ennemies[e].y-1][ennemies[e].x] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/sol2.bmp");
                                ennemies[e].y--;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/ennemi.bmp");
                            }
                            else deplacementMob[e] = 1;
                            break;

                    case 1 : if (labyrinthe[numLab][ennemies[e].y+1][ennemies[e].x] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/sol2.bmp");
                                ennemies[e].y++;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/ennemi.bmp");
                            }
                            else deplacementMob[e] = 0;
                            break;

                    case 2 : if (labyrinthe[numLab][ennemies[e].y][ennemies[e].x-1] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/sol2.bmp");
                                ennemies[e].x--;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/ennemi.bmp");
                            }
                            else deplacementMob[e] = 3;
                            break;

                    case 3 : if (labyrinthe[numLab][ennemies[e].y][ennemies[e].x+1] != '#')
                            {
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = ' ';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/sol2.bmp");
                                ennemies[e].x++;
                                labyrinthe[numLab][ennemies[e].y][ennemies[e].x] = 'E';
                                afficherImage ( ennemies[e].x*25+250, ennemies[e].y*25+150, renderer , "img/ennemi.bmp");
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


            for (int y = 0 ; y < DIMY; y++)
            {
                for(int x = 0 ; x < DIMX; x++)
                {
                    switch(labyrinthe[i][y][x])
                    {
                        case  'o' :
                                    if (change == FALSE)
                                    {
                                        switch (numLab)
                                        {
                                            case 1 :afficherImage ( x*25+250, y*25+150, renderer , "img/piegeF.bmp");break;
                                            case 2 :afficherImage ( x*25+400, y*25+30, renderer , "img/piegeF.bmp");break;
                                        }

                                    }
                                    else if (change == TRUE)
                                    {
                                        switch (numLab)
                                        {
                                            case 1 : afficherImage ( x*25+250, y*25+150, renderer , "img/piegeO.bmp");break;
                                            case 2 : afficherImage ( x*25+400, y*25+30, renderer , "img/piegeO.bmp");break;
                                        }
                                    }break;

                        case  'S' :
                            switch (numLab)
                                        {
                                            case 0 : afficherImage ( x*25+100, y*25+100, renderer , "img/porteF.bmp");break;
                                            case 1 : afficherImage ( x*25+250, y*25+150, renderer , "img/porteF.bmp");break;
                                            case 2 : afficherImage ( x*25+400, y*25+30, renderer , "img/porteF.bmp");break;
                                        }break;

                        case 's' :
                            switch (numLab)
                                        {
                                            case 0 : afficherImage ( x*25+100, y*25+100, renderer , "img/porteO.bmp");break;
                                            case 1 : afficherImage ( x*25+250, y*25+150, renderer , "img/porteO.bmp");break;
                                            case 2 : afficherImage ( x*25+400, y*25+30, renderer , "img/porteO.bmp");break;
                                        }break;

                    }
                }
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
