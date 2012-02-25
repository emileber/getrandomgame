#include "BiomeManager.h"
#include "Biomes/WaterBiome.h"

BiomeManager::BiomeManager()
{

}

BiomeManager::~BiomeManager()
{

}

void BiomeManager::generate(char** map, int mapsize)
{

    for(unsigned int i =0 ;i<biomes.size();i++)
        {
        biomes[i]->Generate(map, mapsize);
        }
}

int BiomeManager::createNewBiome(char t)
{
    switch(t)
    {


    case 'e' :
    {
        biomes.push_back(new WaterBiome(t));
        break;
    }
    default :
    {
        biomes.push_back(new Biome(t));
        break;
    }
    }


    return (biomes.size()-1);
}
