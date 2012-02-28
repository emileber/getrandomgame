#include "ZoneType/SunkenCity.h"
#include "ZoneType/dockQuarter.h"
#include "ZoneType/SpreadRules/Cluster.h"
#include <stdlib.h>


SunkenCity::SunkenCity()
{
    probabilite=2;
    size=2;
    id='U';
    biomeType='e';
    rules = new Cluster();


}
SunkenCity::~SunkenCity()
{

}

SunkenCity::SunkenCity(char** map, point* p) : ZoneType()
{
    map[p->Getx()][p->Gety()]='U';
}
int SunkenCity::Place(char** map, std::vector<point*>* possible, int mapsize)
{

    size = (rand()%10)+1;
    rules->Spread(map,possible,mapsize, id, biomeType, size);
    return size;

}
