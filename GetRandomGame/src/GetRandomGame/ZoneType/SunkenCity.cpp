#include "ZoneType/SunkenCity.h"
#include "ZoneType/DockQuarter.h"
#include <stdlib.h>

SunkenCity::SunkenCity() {
	probabilite = 2;
	size = 2;
}
SunkenCity::~SunkenCity() {

}

SunkenCity::SunkenCity(char** map, point* p) :
		ZoneType() {
	map[p->Getx()][p->Gety()] = 'U';
}
int SunkenCity::Place(char** map, std::vector<point*>* possible, int mapsize) {
	//bool found=false; // unused
	int num = rand() % ((int) (possible->size()));

	size = (rand() % 10) + 1;
	int x = possible->at(num)->Getx();
	int y = possible->at(num)->Gety();
	map[x][y] = 'U';

	for (int i = 0; i < size - 1; i++) {
		//determine par ou la ville pousse
		int dirX = 0;
		int dirY = 0;
		while (dirX == 0 && dirY == 0) {
			dirX = (rand() % 3) - 1;
			dirY = (rand() % 3) - 1;
		}

		bool found = false;
		int devX = 0;
		int devY = 0;
		//tant qu'on a pas trouver une case on va avancer dans le même direction
		while (!found) {
			devX += (dirX);
			devY += (dirY);
			if (devX + x < 0 || devY + y < 0 || devX + x >= mapsize
					|| devY + y >= mapsize) {
				//on se cancel en atteignant le bord de la map
				found = true;
				return (0);
			}
			if (map[x + devX][y + devY] == 'e') {
				map[x + devX][y + devY] = 'U';
				found = true;
			}
		}

	}

	return num;

}
