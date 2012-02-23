#ifndef dock_H
#define dock_H
#include "zoneType.h"


class docks : public zoneType
{
    public:
        docks();
        docks(char** map, point* p);
        virtual ~docks();
        virtual int place(char** map, std::vector<point*>* possible, int mapsize);
    protected:
    private:
};

#endif // dock_H
