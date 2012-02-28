#include "WaterBiome.h"
#include <stdlib.h>
#include <iostream>
#include "ZoneType/Docks.h"
#include "ZoneType/SunkenCity.h"
#include "ZoneType/ShipGraveyard.h"

WaterBiome::WaterBiome(char t) :
		Biome(t) {
	possibleZoneTypes.push_back(new Docks());
	possibleZoneTypes.push_back(new SunkenCity());
	possibleZoneTypes.push_back(new ShipGraveyard());
}

WaterBiome::~WaterBiome() {
	//dtor
}


