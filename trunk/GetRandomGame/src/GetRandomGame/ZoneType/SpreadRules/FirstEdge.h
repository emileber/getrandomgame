#ifndef FirstEdge_H
#define FirstEdge_H
#include "SpreadRules.h"


class FirstEdge : public SpreadRules
{
    public:
        FirstEdge(){};
        virtual ~FirstEdge(){};
        virtual void Spread(char** map, std::vector<point*>* possible, int mapsize, char type , char biomeType, int nb);
    protected:
    private:
};
#endif
