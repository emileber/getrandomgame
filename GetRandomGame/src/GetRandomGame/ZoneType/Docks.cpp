#include "ZoneType/Docks.h"
#include "ZoneType/DockQuarter.h"
#include <stdlib.h>

Docks::Docks() {
	probabilite = 4;
	size = 1;
}
Docks::~Docks() {

}

Docks::Docks(char** map, point* p) :
		ZoneType() {
	map[p->Getx()][p->Gety()] = 'd';
}
int Docks::Place(char** map, std::vector<point*>* possible, int mapsize) {
	bool found = false;
	int i = rand() % ((int) (possible->size()));
	while (!found) {
		//on va cherche a traver le vecteur de points possible le premier point qui aura un voisin qui n'est pas de l'eau
		i %= possible->size();
		int j = -1;
		while (++j < 3 && !found) {
			int newX = possible->at(i)->Getx() + j - 1;
			if (newX >= 0 && newX < mapsize) {

				if (map[newX][possible->at(i)->Gety()] != 'e'
						&& map[newX][possible->at(i)->Gety()] != 'k'
						&& map[newX][possible->at(i)->Gety()] != 'Q') {
					found = true;
					map[newX][possible->at(i)->Gety()] = 'Q';

					return (i);
				}
			}

		}
		j = -1;
		while (++j < 3 && !found) {
			int newY = possible->at(i)->Gety() + j - 1;
			if (newY >= 0 && newY < mapsize) {
				if (map[possible->at(i)->Getx()][newY] != 'e'
						&& map[possible->at(i)->Getx()][newY] != 'Q'
						&& map[possible->at(i)->Getx()][newY] != 'k') {
					found = true;
					map[possible->at(i)->Getx()][newY] = 'Q';

					return (i);
				}
			}

		}
		i++;
	}
	return -1; // TODO check that DUPA
}
