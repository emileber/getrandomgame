#ifndef DIAMONDSQUARE_H_INCLUDED
#define DIAMONDSQUARE_H_INCLUDED

class DiamondSquare
{
    private :

    int iteration;
    int sidesize;
    float smoother;
    int sideSize;
    int arraySize;
    float randomRange;

    void DoDiamond(int** tableau);
    void DoSquare(int** tableau);

    public :

    DiamondSquare(){};
    void Randomize(int** tableau, float smoothing, int seed, int rRange, int ize, int it=0);
    int** getArray(int size);

};

#endif // DIAMONDSQUARE_H_INCLUDED
