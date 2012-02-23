#ifndef MAPGENERATOR_H_INCLUDED
#define MAPGENERATOR_H_INCLUDED

#include "WorldMap.h"
#include "DiamondSquare.h"
#include <stdint.h>
#include "Biome.h"
#include "point.h"
#include "BiomeManager.h"

//made by DUPA
//pour l'instant un bonne partie des mondes sont cools, les biomes froid et tempérés sont bien balancé, reste juste a revoir les biomes chaud vu qu'on me criss souvent de la forêt tropicale pis de la savnne un a coté de l'autre...


class MapGenerator {

private:
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
	int tempDeviation;//plus c'est haut plus les température auc poles sont basse et a l'Équateur sont chaude


	void SkewHuMap();
	void SkewVMap();
	void SkewTMap();
	void CreateBiomesMap();
	void BiomesParser(char type, bool** check ,point* debut, BiomeManager* bManager, int num);
	void CreateBiomes();

public:
	MapGenerator();
	WorldMap* GenerateANewWorld(int size, float smoothing, int rRange,
			uint32_t seed);
	template<class T>
	T** getArray(int size);
};

#endif

