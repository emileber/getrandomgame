#ifndef dock_H
#define dock_H
#include "ZoneType.h"

class Docks: public ZoneType {
public:
	Docks();
	Docks(char** map, point* p);
	virtual ~Docks();
	virtual int Place(char** map, std::vector<point*>* possible, int mapsize);
protected:
private:
};

#endif // dock_H
