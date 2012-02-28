#ifndef ZONETYPE_H
#define ZONETYPE_H
#include "point.h"
#include "ZoneType/SpreadRules/SpreadRules.h"
#include <vector>

class ZoneType
{
    public:
        ZoneType();
        ~ZoneType();
        virtual int Place(char** map, std::vector<point*>* possible, int mapsize)=0;
        //le vecteur est la parceque dans le meilleur des cas les objet d plus de 1 tile vont deleter leurs points tous seuls
        int GetProb(){return probabilite;}
        int GetSize(){return size;}
    protected:
    int probabilite;
    int size;
    char id;
    char biomeType;
    SpreadRules* rules;

    private:
};

#endif // ZONETYPE_H
