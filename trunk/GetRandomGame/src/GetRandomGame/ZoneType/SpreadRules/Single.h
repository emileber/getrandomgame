#ifndef Single_H
#define Single_H
#include "SpreadRules.h"


class Single : public SpreadRules
{
    public:
        Single(){};
        virtual ~Single(){};
        virtual void Spread(char** map, std::vector<point*>* possible, int mapsize, char type , char biomeType, int nb);
    protected:
    private:
};
#endif
