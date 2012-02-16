#ifndef MAPGENERATOR_H_INCLUDED
#define MAPGENERATOR_H_INCLUDED

#include "WorldMap.h"
#include "DiamondSquare.h"

//made by DUPA
//pour l'instant un bonne partie des mondes sont cools, les biomes froid et temp�r�s sont bien balanc�, reste juste a revoir les biomes chaud vu qu'on me criss souvent de la for�t tropicale pis de la savnne un a cot� de l'autre...

class MapGenerator
{

    private :
    WorldMap* map;
    int mapSize;

   int waterHeatRange;
    int heightToTLoss;
    int extremeT;
    int temptoHuRatio;
    int WaterHuRange;
    int montainHuRange;
    int waterHuModifier;
    int waterHeatModifier;

    void SkewHuMap();
    void SkewVMap();
    void SkewTMap();
    void CreateBiomesMap();

    public :
    MapGenerator();
    WorldMap* GenerateANewWorld(int size,float smoothing, int rRange, int seed);
    template <class T>
    T** getArray(int size);
};

#endif


