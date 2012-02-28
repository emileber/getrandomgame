#include "ZoneType/ShipGraveyard.h"
#include "ZoneType/dockQuarter.h"
#include "ZoneType/SpreadRules/Single.h"
#include <stdlib.h>


ShipGraveyard::ShipGraveyard()
{
    probabilite=1;
    size=1;
    id='Y';
    biomeType='e';
    rules = new Single();


}
ShipGraveyard::~ShipGraveyard()
{

}

ShipGraveyard::ShipGraveyard(char** map, point* p) : ZoneType()
{
    map[p->Getx()][p->Gety()]='Y';
}
int ShipGraveyard::Place(char** map, std::vector<point*>* possible, int mapsize)
{


    rules->Spread(map,possible,mapsize, id, biomeType, 1);
    return size;

}
