#ifndef ShipGraveyard_H
#define ShipGRaveyard_H
#include "ZoneType.h"


class ShipGraveyard : public ZoneType
{
    public:
        ShipGraveyard();
        ShipGraveyard(char** map, point* p);
        virtual ~ShipGraveyard();
        virtual int Place(char** map, std::vector<point*>* possible, int mapsize);
    protected:
    private:
};

#endif // dock_H
