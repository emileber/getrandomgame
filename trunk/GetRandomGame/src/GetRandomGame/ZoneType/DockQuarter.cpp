#include "ZoneType/dockQuarter.h"

dockQuarter::dockQuarter(char** map, point* p) : zoneType()
{
    map[p->Getx()][p->Gety()]='Q';
}
