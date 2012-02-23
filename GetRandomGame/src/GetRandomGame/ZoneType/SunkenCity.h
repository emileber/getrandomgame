#ifndef SunkenCity_H
#define SunkenCity_H
#include "zoneType.h"


class SunkenCity : public zoneType
{
    public:
        SunkenCity();
        SunkenCity(char** map, point* p);
        virtual ~SunkenCity();
        virtual int place(char** map, std::vector<point*>* possible, int mapsize);
    protected:
    private:
};

#endif // dock_H
