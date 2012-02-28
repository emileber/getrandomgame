#ifndef Cluster_H
#define Cluster_H
#include "SpreadRules.h"


class Cluster : public SpreadRules
{
    public:
        Cluster(){};
        virtual ~Cluster(){};
        virtual void Spread(char** map, std::vector<point*>* possible, int mapsize, char type , char biomeType, int nb);
    protected:
    private:
};
#endif
