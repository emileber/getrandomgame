#include "FirstEdge.h"
#include <stdlib.h>
void FirstEdge::Spread(char** map, std::vector<point*>* possible, int mapsize, char typePlaced, char biomeType, int nb)
{

    for (int k=0;k<nb;k++)
    {


        bool found = false;
        int i = rand() % ((int) (possible->size()));
        while (!found) {
            //on va cherche a traver le vecteur de points possible le premier point qui aura un voisin qui n'est pas de l'eau
            i %= possible->size();
            int j = -1;
            while (++j < 3 && !found) {
                int newX = possible->at(i)->Getx() + j - 1;
                if (newX >= 0 && newX < mapsize) {

                    if (map[newX][possible->at(i)->Gety()] != biomeType
                            && map[newX][possible->at(i)->Gety()] != typePlaced) {
                        found = true;
                        map[newX][possible->at(i)->Gety()] = typePlaced;

                        possible->erase(possible->begin()+i);
                    }
                }

            }
            j = -1;
            while (++j < 3 && !found) {
                int newY = possible->at(i)->Gety() + j - 1;
                if (newY >= 0 && newY < mapsize) {
                    if (map[possible->at(i)->Getx()][newY] != biomeType
                            && map[possible->at(i)->Getx()][newY] != typePlaced) {
                        found = true;
                        map[possible->at(i)->Getx()][newY] = typePlaced;

                        possible->erase(possible->begin()+i);
                    }
                }

            }
            i++;
        }
    }
}
