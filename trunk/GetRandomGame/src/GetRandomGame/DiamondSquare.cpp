#include "DiamondSquare.h"
#include <stdlib.h>
//made bu DUPA


void DiamondSquare::Randomize(int** tableau, float smoothing, int rRange,int size, float pFactor, int it)
{
    arraySize = size;
    sideSize = arraySize-1;
    iteration=it;
    randomRange=rRange;
    smoother=smoothing;
    positiveFactor=pFactor;

    if(it==0)
    {
        tableau[0][size-1]= (rand()%rRange)-rRange/2;
        tableau[size-1][size-1]= (rand()%rRange)-rRange/2;
        tableau[0][0]= (rand()%rRange)-rRange/2;
        tableau[size-1][0]= (rand()%rRange)-rRange/2;
    }
    for(int i =0; i<it;i++)
    {
        sideSize=sideSize/2;
        randomRange=randomRange/smoother;
    }
    halfSide=sideSize/2;

    while(sideSize>1)
    {
        DoDiamond(tableau);
        DoSquare(tableau);
        it++;
        sideSize=sideSize/2;
        randomRange=randomRange/smoother;
        halfSide=sideSize/2;

    }


}

void DiamondSquare::DoDiamond(int** tableau)
{

    double moyenne;

    for(int x = 0;x<arraySize-1;x+=sideSize)
    {
        for(int y = 0;y<arraySize-1;y+=sideSize)
        {
            moyenne=(tableau[x][y]+tableau[x+sideSize][y+sideSize]+tableau[x+sideSize][y]+tableau[x][y+sideSize])/4;
            int lerandom = ((rand() % ((int)randomRange*2))-randomRange)+(randomRange*positiveFactor);
            tableau[x+halfSide][y+halfSide]=moyenne + lerandom+tableau[x+halfSide][y+halfSide];
        }
    }


}

void DiamondSquare::DoSquare(int** tableau)
{

    int moyenne;

    for(int x=0;x<arraySize;x+=halfSide)
    {
        for(int y=(x+halfSide)%sideSize;y<arraySize;y+=sideSize)
        {
            moyenne = (tableau[((x-halfSide)+arraySize)%arraySize][y] + tableau[(x+halfSide)%arraySize][y] + tableau[x][(y+halfSide)%arraySize] + tableau[x][(y-halfSide+arraySize)%arraySize])/4;
            int lerandom = ((rand() % ((int)randomRange*2))-randomRange)+(positiveFactor*randomRange);
            tableau[x][y]= moyenne + lerandom+tableau[x][y];
        }
    }
}





