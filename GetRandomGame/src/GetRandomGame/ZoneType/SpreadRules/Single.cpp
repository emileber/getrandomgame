#include "Single.h"
#include <stdlib.h>
void Single::Spread(char** map, std::vector<point*>* possible, int mapsize, char typePlaced, char biomeType, int nb)
{

    for (int k=0;k<nb;k++)
    {



        int i = rand() % ((int) (possible->size()));

        map[possible->at(i)->Getx()][possible->at(i)->Gety()] = typePlaced;
        possible->erase(possible->begin()+i);
    }

}
