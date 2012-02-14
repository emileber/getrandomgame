/*
 * WorldMap.cpp
 *
 *  Created on: 2012-02-14
 *      Author: Emile
 */

#include "WorldMap.h"
#include "DiamondSquare.h"
#include <iostream>

using namespace std;

WorldMap::WorldMap() {
	DiamondSquare* ds = new DiamondSquare();
	int** tab = ds->getArray(65);

	ds->Randomize(tab, 2, 23534, 40, 65);

	for (int i = 0; i < 65; i++) {
		for (int j = 0; j < 65; j++) {
			//cout << tab[j][i] << '\t';
			if (tab[j][i] < 0) {
				cout << "~";
			} else if ((tab[j][i] < 10) && (tab[j][i] >= 0)) {
				cout << "p";
			} else if ((tab[j][i] < 20) && (tab[j][i] >= 10)) {
				cout << "h";
			} else if (tab[j][i] >= 20) {
				cout << "M";
			}
		}
		cout << endl;
	}

}

WorldMap::~WorldMap() {
	// TODO Auto-generated destructor stub
}

void WorldMap::update() {
}

void WorldMap::draw() {
}

