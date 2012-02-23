#ifndef BIOME_H
#define BIOME_H

#include "point.h"
#include "ZoneType/zoneType.h"

#include<vector>
using namespace std;


class Biome
{
    public:
        Biome(char t);
        virtual ~Biome();
        vector<point*> Gettile() { return tile; }

        void Settile(vector<point*> val) { tile = val; }
        void AddTile(point* t) { tile.push_back(t); }
        char Gettype() { return type; }
        void Settype(char val) { type = val; }

        virtual int generate(char** map,int mapsize){return 0;}

    protected:
        vector<point*> tile;
        vector<zoneType*> possibleZoneTypes;
        char type;
};

#endif // BIOME_H
