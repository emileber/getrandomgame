#include "WaterBiome.h"
#include <stdlib.h>
#include <iostream>
#include "ZoneType/Docks.h"
#include "ZoneType/SunkenCity.h"

WaterBiome::WaterBiome(char t) :
		Biome(t) {
	possibleZoneTypes.push_back(new Docks());
	possibleZoneTypes.push_back(new SunkenCity());
}

WaterBiome::~WaterBiome() {
	//dtor
}

int WaterBiome::Generate(char** map, int mapsize) {
	int probtotal = 0;
	int maxType = tile.size() / 100;
	//on va faire des zones sp�ciales jusqu'a maxTile
	// la zone choisi est determin� par la prob dans la zoneType/le total des probs, donc plus ya de type different moin chauqe type a de probabilit� d'rriv�.
	for (unsigned int i = 0; i < possibleZoneTypes.size(); i++) {
		probtotal += possibleZoneTypes[i]->getProb();
	}

	while (maxType > 0) {
		int range = (rand() % probtotal) + 1;
		int probnow = 0;
		int i = 0;
		while (range > probnow) {
			probnow += possibleZoneTypes[i]->getProb();
			i++;
		}
		i--;
		//on flush la tile qui a �t� picker.
		int toErase = possibleZoneTypes[i]->Place(map, &tile, mapsize);
		tile.erase(tile.begin() + toErase);
		maxType -= possibleZoneTypes[i]->getSize();
	}
	return -1;
}
