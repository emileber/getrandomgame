#ifndef SpreadRules_H
#define SpreadRules_H
#include "point.h"
#include <vector>


class SpreadRules
{
    public:
        SpreadRules(){};
        virtual ~SpreadRules(){};
        virtual void Spread(char** map, std::vector<point*>* possible, int mapsize, char type , char biomeType, int nb)=0;
    protected:
    private:
};
#endif
