#include "ZoneType/Docks.h"
#include "ZoneType/DockQuarter.h"
#include "ZoneType/SpreadRules/FirstEdge.h"
#include <stdlib.h>

Docks::Docks() {
    probabilite=4;
    id='k';
    size=1;
    biomeType='e';
    rules = new FirstEdge();
}
Docks::~Docks() {

}

Docks::Docks(char** map, point* p) :
		ZoneType() {
	map[p->Getx()][p->Gety()] = 'd';
}
int Docks::Place(char** map, std::vector<point*>* possible, int mapsize) {
	int size = (rand()%3)+1;
	rules->Spread(map,possible, mapsize, id, biomeType, size);
	return size; // TODO check that DUPA
}
