#include "Biome.h"
#include <stdlib.h>

Biome::Biome(char t)
{
    type=t;
}

Biome::~Biome()
{
    //dtor
}

void Biome::Generate(char** map, int mapsize )
{
    int probtotal = 0;
	int maxType = tile.size() / 100;
	//on va faire des zones sp�ciales jusqu'a maxTile
	// la zone choisi est determin� par la prob dans la zoneType/le total des probs, donc plus ya de type different moin chauqe type a de probabilit� d'rriv�.
	for (unsigned int i = 0; i < possibleZoneTypes.size(); i++) {
		probtotal += possibleZoneTypes[i]->GetProb();
	}
    if(probtotal>0)
    {

        while (maxType > 0) {
            int range = (rand() % probtotal) + 1;
            int probnow = 0;
            int i = 0;
            while (range > probnow) {
                probnow += possibleZoneTypes[i]->GetProb();
                i++;
            }
            i--;
            //on flush la tile qui a �t� picker.
            int size = possibleZoneTypes[i]->Place(map, &tile, mapsize);
            maxType -= size;
        }
    }

}
