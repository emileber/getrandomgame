#ifndef ZONETYPE_H
#define ZONETYPE_H
#include "point.h"
#include <vector>

class zoneType
{
    public:
        zoneType();
        ~zoneType();
        virtual int place(char** map, std::vector<point*>* possible, int mapsize)=0;
        //le vecteur est la parceque dans le meilleur des cas les objet d plus de 1 tile vont deleter leurs points tous seuls
        int getProb(){return probabilite;}
        int getSize(){return size;}
    protected:
    int probabilite;
    int size;
    private:
};

#endif // ZONETYPE_H
