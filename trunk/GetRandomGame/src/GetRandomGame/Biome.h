#ifndef BIOME_H
#define BIOME_H

#include "point.h"
#include "ZoneType/ZoneType.h"

#include<vector>
using namespace std;


class Biome
{
    public:
        Biome(char t);
        virtual ~Biome();
        vector<point*> Gettile() { return tile; }

        void SetTile(vector<point*> val) { tile = val; }
        void AddTile(point* t) { tile.push_back(t); }
        char Gettype() { return type; }
        void Settype(char val) { type = val; }

        virtual void Generate(char** map,int mapsize);

    protected:
        vector<point*> tile;
        vector<ZoneType*> possibleZoneTypes;
        char type;
};

#endif // BIOME_H
