#ifndef SunkenCity_H
#define SunkenCity_H
#include "ZoneType.h"


class SunkenCity : public ZoneType
{
    public:
        SunkenCity();
        SunkenCity(char** map, point* p);
        virtual ~SunkenCity();
        virtual int Place(char** map, std::vector<point*>* possible, int mapsize);
    protected:
    private:
};

#endif // dock_H
