


#ifndef WATERBIOME_H
#define WATERBIOME_H
#include "Biome.h"

class WaterBiome: public Biome {
public:
	WaterBiome(char t);
	virtual ~WaterBiome();
	int Generate(char** map, int mapsize);

protected:
private:
};

#endif // EAU_H
