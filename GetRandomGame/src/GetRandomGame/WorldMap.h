/*
 * WorldMap.h
 *
 *  Created on: 2012-02-14
 *      Author: Emile
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_
#include "World.h"
#include "Graphic/GraphicType.h" // Color3f et SectionRect

// pas de using namespace ici

/*
 *
 */
class WorldMap: public TileEngine::World {


private :
    int** hMap;
    int** vMap;
    int** huMap;
    int** tMap;
    char** biomesMap;
    int mapSize;

    float mScale;

public:
	WorldMap(int size);
	virtual ~WorldMap();
	virtual void Update();
	virtual void Draw();
	void DropXML();

	int** getHMap(){return hMap;}
	int** getHuMap(){return huMap;}
	int** getVMap(){return vMap;}
	int** getTMap(){return tMap;}
	char** getBiomesMap(){return biomesMap;}

	TileEngine::Color3f * getTint(int x, int y);

	void Scale(float ratio); // just to test the scale function

	void setBiomesMap(char** map){biomesMap=map;}
	void setHMap(int** map){hMap=map;}
	void setHuMap(int** map){huMap=map;}
	void setVMap(int** map){vMap=map;}
	void setTMap(int** map){tMap=map;}


};

#endif /* WORLDMAP_H_ */
