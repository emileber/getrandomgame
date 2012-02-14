#include "DiamondSquare.h"
#include <stdlib.h>


void DiamondSquare::Randomize(int** tableau, float smoothing, int seed, int rRange,int size, int it)
{
    arraySize = size;
    sideSize = arraySize-1;
    iteration=it;
    randomRange=rRange;
    smoother=smoothing;
    srand(seed);
    for(int i =0; i<it;i++)
    {
        sideSize=sideSize/2;
        randomRange=randomRange/smoother;
    }


    while(sideSize>1)
    {
        DoDiamond(tableau);
        DoSquare(tableau);
        it++;
        sideSize=sideSize/2;
        randomRange=randomRange/smoother;

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
            int lerandom = (rand() % ((int)randomRange*2))-randomRange;
            tableau[x+sideSize/2][y+sideSize/2]=moyenne + lerandom;
        }
    }


}

void DiamondSquare::DoSquare(int** tableau)
{

    int moyenne;

    for(int x=0;x<arraySize;x+=sideSize/2)
    {
        for(int y=(x+sideSize/2)%sideSize;y<arraySize;y+=sideSize)
        {
            moyenne = (tableau[((x-sideSize/2)+arraySize)%arraySize][y] + tableau[(x+sideSize/2)%arraySize][y] + tableau[x][(y+sideSize/2)%arraySize] + tableau[x][(y-sideSize/2+arraySize)%arraySize])/4;
            int lerandom = (rand() % ((int)randomRange*2))-randomRange;
            tableau[x][y]= moyenne + lerandom;
        }
    }
}

int** DiamondSquare::getArray(int size)
{
    int **board=new int*[size];
    for (int i=0; i<size; i++)
    {
       board[i] = new int[size];
       for (int j=0; j<size; j++)
         board[i][j]=0;
    }

    return board;


}

