#ifndef MAPGENERATOR_H_INCLUDED
#define MAPGENERATOR_H_INCLUDED

#include "WorldMap.h"
#include "DiamondSquare.h"

//made by DUPA
//pour l'instant un bonne partie des mondes sont cools, les biomes froid et tempérés sont bien balancé, reste juste a revoir les biomes chaud vu qu'on me criss souvent de la forêt tropicale pis de la savnne un a coté de l'autre...

class MapGenerator
{

    private :
    WorldMap* map;
    int mapSize;

    void SkewHuMap();
    void SkewVMap();
    void SkewTMap();
    void CreateBiomesMap();

    public :
    MapGenerator();
    WorldMap* GenerateANewWorld(int size,float smoothing, int rRange);
    template <class T>
    T** getArray(int size);
};

#endif


