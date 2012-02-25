#ifndef dockQuarter_H
#define dockQuarter_H
#include "ZoneType.h"
#include "Point.h"
#include <vector>


class DockQuarter : public ZoneType
{
    public:
        DockQuarter();
        DockQuarter(char** map, point* p);
        virtual ~DockQuarter(){};
        virtual int place(char** map, std::vector<point*>* possible, int mapsize){return 0;};
    protected:
    private:
};

#endif // dock_H
