#include<vector>
#include "Biome.h"

class BiomeManager
{
    public:
        BiomeManager();
        virtual ~BiomeManager();
        Biome* GetBiome(int n) { return biomes.at(n); }



        int createNewBiome(char t);

        void generate(char** map, int mapsize);

    protected:
    private:
        vector<Biome*> biomes;
};
