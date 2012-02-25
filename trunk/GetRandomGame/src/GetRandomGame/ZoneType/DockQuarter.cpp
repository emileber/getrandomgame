#include "ZoneType/DockQuarter.h"

DockQuarter::DockQuarter(char** map, point* p) : ZoneType()
{
    map[p->Getx()][p->Gety()]='Q';
}
