#ifndef DIAMONDSQUARE_H_INCLUDED
#define DIAMONDSQUARE_H_INCLUDED
//made by dUPA

class DiamondSquare
{
    private :

    int iteration;
    int sidesize;
    float smoother;
    int sideSize;
    int arraySize;
    int halfSide;
    float randomRange;
    //un chiffre de 1 a -1 qui tire la map ver le postif ou le negatif
    float positiveFactor;

    void DoDiamond(int** tableau);
    void DoSquare(int** tableau);

    public :

    DiamondSquare(){};
    void Randomize(int** tableau, float smoothing, int rRange, int size, float pFactor, int it=0);


};

#endif // DIAMONDSQUARE_H_INCLUDED
