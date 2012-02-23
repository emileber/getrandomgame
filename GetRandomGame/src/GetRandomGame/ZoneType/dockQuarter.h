#ifndef dockQuarter_H
#define dockQuarter_H
#include "zoneType.h"
#include "point.h"
#include <vector>


class dockQuarter : public zoneType
{
    public:
        dockQuarter();
        dockQuarter(char** map, point* p);
        virtual ~dockQuarter(){};
        virtual int place(char** map, std::vector<point*>* possible, int mapsize){};
    protected:
    private:
};

#endif // dock_H
