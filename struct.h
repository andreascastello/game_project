#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct
{
    int x;
    int y;
}
Coordonnees;

typedef struct
{
    Coordonnees Porte;
    Coordonnees Clees;
    int laby;
    int iDpassage;
    int Verrouillage;
}
Passage;

#endif // STRUCTURES_H_INCLUDED
