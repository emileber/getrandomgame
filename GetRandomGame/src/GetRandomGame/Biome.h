#ifndef BIOME_H
#define BIOME_H

#include "point.h"

#include<vector>
using namespace std;


class Biome
{
    public:
        Biome();
        virtual ~Biome();
        vector<point> Gettile() { return tile; }

        void Settile(vector<point> val) { tile = val; }
        char Gettype() { return type; }
        void Settype(char val) { type = val; }

        void generate(){};

    protected:
    private:
        vector<point> tile;
        char type;
};

#endif // BIOME_H
