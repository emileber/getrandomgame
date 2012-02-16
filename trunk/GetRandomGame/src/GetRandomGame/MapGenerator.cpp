#include "MapGenerator.h"
#include <iostream>

using namespace std;
MapGenerator::MapGenerator()
{
    map = new WorldMap(0);
    waterHeatRange=5;
    waterHeatModifier=3;
    heightToTLoss=8;
    extremeT=14;
    temptoHuRatio=4;
    WaterHuRange=9;
    montainHuRange=9;
    waterHuModifier=4;
}

WorldMap* MapGenerator::GenerateANewWorld(int size,float smoothing, int rRange, int seed)
{
    //delete(map);

    map = new WorldMap(size);
    map->setHMap(getArray<int>(size));
    map->setHuMap(getArray<int>(size));
    map->setTMap(getArray<int>(size));
    map->setVMap(getArray<int>(size));
    map->setBiomesMap(getArray<char>(size));
    mapSize=size;
    DiamondSquare* ds = new DiamondSquare();
    std::cout<<"got a map"<<std::endl;
    ds->Randomize(map->getHMap(),smoothing, seed++, rRange, size, 0.15);

std::cout<<"got a hmap"<<std::endl;



    ds->Randomize(map->getTMap(),smoothing, seed++, rRange, size,0.2);
    std::cout<<"got a Tmap"<<std::endl;
    SkewTMap();

    ds->Randomize(map->getHuMap(),smoothing, seed++, rRange, size,0);
    std::cout<<"got a HUmap"<<std::endl;
    SkewHuMap();


    ds->Randomize(map->getVMap(),smoothing, seed++, rRange, size,0);
    std::cout<<"got a Vmap"<<std::endl;
    SkewVMap();
    CreateBiomesMap();
    std::cout<<"got a Bmap"<<std::endl;

    return map;
}

void MapGenerator::SkewTMap()
{
    int** tMap = map->getTMap();
    int** hMap = map->getHMap();
    //la map de température est plus froide aux poles et en hauteur, plus chaude autour de l'eau
    for(int y =0; y<mapSize; y++)
    {
        //les 3 prochaines lignes batissent un fonction absolu inversé, qui peak au millieu de la map
        int baseT = y-((mapSize-1)/2);

        baseT = ((baseT >= 0) ? -baseT : baseT);

        baseT+=(mapSize-1)/3;



        for(int x=0; x<mapSize; x++)
        {
            if(hMap[x][y]<0)
            {
                for(int i =0; i<waterHeatRange; i++)
                {
                    for(int j =0; j<waterHeatRange;j++)
                    {
                        if((x-(waterHeatRange-1)/2+i)>0&&(x-2+i)<mapSize&&(y-(waterHeatRange-1)/2+i)>0&&(y-(waterHeatRange-1)/2+i)<mapSize)
                            tMap[x-(waterHeatRange-1)/2+i][y-(waterHeatRange-1)/2+j]+=waterHeatModifier;
                    }
                }
            }
            tMap[x][y]+=(baseT-(hMap[x][y]/heightToTLoss));

        }

    }
}

void MapGenerator::SkewHuMap()
{
    int** tMap = map->getTMap();
    int** hMap = map->getHMap();
    int** huMap = map->getHuMap();
    int halfMap=((mapSize-1)/2);

    //les océans augmentent l'humidité autour d'eux
    //Les températures extremes diminuent l'humidité
    for(int y =0; y<mapSize; y++)
    {

        for(int x=0; x<mapSize; x++)
        {
             int hemisphereMod;
            int absTemp = ((tMap[x][y] >= 0) ? -tMap[x][y] : tMap[x][y]);
            absTemp+=extremeT;
            huMap[x][y]+=absTemp/temptoHuRatio;
            if(hMap[x][y]<0)
            {
                for(int i =0; i<WaterHuRange; i++)
                {
                    for(int j =0; j<WaterHuRange;j++)
                    {
                        if((x-(WaterHuRange-1)/2+i)>0&&(x-2+i)<mapSize&&(y-WaterHuRange+i)>0&&(y-WaterHuRange+i)<mapSize)
                            huMap[x-(WaterHuRange-1)/2+i][y-(WaterHuRange-1)/2+j]+=waterHuModifier;
                    }
                }
            }

        }

    }
}

void MapGenerator::SkewVMap()
{
    int** tMap = map->getTMap();
    int** hMap = map->getHMap();
    int** vMap = map->getVMap();
    int** huMap = map->getHuMap();
    //la vegetation est moin abondante dans le froid et en millieu sec et en hauteur et en mer...
    for(int y =0; y<mapSize; y++)
    {



        for(int x=0; x<mapSize; x++)
        {
            vMap[x][y]+=(((tMap[x][y]*hMap[x][y])/16)-hMap[x][y]/4)+huMap[x][y]/4;

        }

    }
}
void MapGenerator::CreateBiomesMap()
{
    int** tMap = map->getTMap();
    int** hMap = map->getHMap();
    int** vMap = map->getVMap();
    int** huMap = map->getHuMap();


    char** biomeMap = map->getBiomesMap();

    for(int y =0; y<mapSize; y++)
    {
        for(int x=0; x<mapSize; x++)
        {
            //jva faire un tableau pour cette partie la...
            if(hMap[x][y]<0)
            {
                biomeMap[x][y]='e';//eau
            }

            else
            {
                if(hMap[x][y]>30)
                {
                     biomeMap[x][y]='M';//montagne
                }
                else
                {
                    if(hMap[x][y]>20)
                    {
                        biomeMap[x][y]='A';//grosse montagne
                    }
                    else
                    {
                        if(tMap[x][y]>30)
                        {
                            if(huMap[x][y]>20)
                            {
                                if(vMap[x][y]>30)
                                {
                                    biomeMap[x][y]='W';//Wild Jungle
                                }
                                else{
                                    if(vMap[x][y]>20)
                                    {
                                        biomeMap[x][y]='J';//Jungle
                                    }
                                    else
                                    {
                                        if(vMap[x][y]>0)
                                        {
                                            biomeMap[x][y]='s';//flooded savannah
                                        }
                                        else
                                        {
                                            biomeMap[x][y]='R'; // Rainy Grassland
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(huMap[x][y]>0)
                                {
                                    if(vMap[x][y]>20)
                                    {
                                        biomeMap[x][y]='J';//Jungle
                                    }
                                    else
                                    {
                                        if(vMap[x][y]>0)
                                        {
                                            biomeMap[x][y]='S';//Savannah
                                        }
                                        else
                                        {
                                            biomeMap[x][y]='G'; //Grassland
                                        }
                                    }
                                }
                                else
                                 {
                                    if(vMap[x][y]>20)
                                    {
                                        biomeMap[x][y]='S';//Savannah
                                    }
                                    else
                                    {
                                        if(vMap[x][y]>0)
                                        {
                                            biomeMap[x][y]='d';//draught-friendly badlands
                                        }
                                        else
                                        {
                                            biomeMap[x][y]='D'; //Arid Desert
                                        }
                                    }
                                }
                             }
                        }
                        else
                        {
                            if(tMap[x][y]>20)
                            {
                                 if(huMap[x][y]>20)
                                {
                                    if(vMap[x][y]>20)
                                    {
                                        biomeMap[x][y]='P';//Swamp
                                    }
                                    else
                                    {
                                        if(vMap[x][y]>0)
                                        {
                                            biomeMap[x][y]='h';//marsh
                                        }
                                        else
                                        {
                                            biomeMap[x][y]='G'; //Grassland
                                        }
                                    }
                                }
                                else
                                {
                                    if(huMap[x][y]>0)
                                    {
                                        if(vMap[x][y]>20)
                                        {
                                            biomeMap[x][y]='F';//feuillus
                                        }
                                        else
                                        {
                                            if(vMap[x][y]>0)
                                            {
                                                biomeMap[x][y]='B';//woodland
                                            }
                                            else
                                            {
                                                biomeMap[x][y]='G'; //Grassland
                                            }
                                        }
                                    }
                                    else
                                     {

                                        if(vMap[x][y]>0)
                                        {
                                            biomeMap[x][y]='G';//Grassland
                                        }
                                        else
                                        {
                                            biomeMap[x][y]='d'; //Desert
                                        }

                                    }
                                 }
                            }
                            else
                            {
                                if(tMap[x][y]>0)
                                {

                                     if(huMap[x][y]>0)
                                    {

                                        if(vMap[x][y]>20)
                                        {
                                            biomeMap[x][y]='C';//Boreal forest
                                        }
                                        else
                                        {
                                            if(vMap[x][y]>0)
                                            {
                                                biomeMap[x][y]='B';//woodland
                                            }
                                            else
                                            {
                                                biomeMap[x][y]='b' ;//boreal grassland
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if(vMap[x][y]>30)
                                        {
                                            biomeMap[x][y]='C';//Boreal forest
                                        }
                                        else
                                        {


                                            if(vMap[x][y]>20)
                                            {
                                                biomeMap[x][y]='B';//woodland
                                            }
                                            else
                                            {

                                                biomeMap[x][y]='b';//boreal grassland

                                            }
                                        }
                                    }

                                }
                                else
                                {
                                    if(huMap[x][y]>0)
                                    {
                                        if(vMap[x][y]>20)
                                        {
                                            biomeMap[x][y]='Z';//Frozen Forest
                                        }
                                        else
                                        {

                                                biomeMap[x][y]='I';//Taiga

                                        }
                                    }
                                    else
                                    {

                                        if(vMap[x][y]>20)
                                        {
                                            biomeMap[x][y]='I';//taiga
                                        }
                                        else
                                        {
                                            biomeMap[x][y]='H';//Thundra



                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }

        }



        }


}

template <class T>
T** MapGenerator::getArray(int size)
{
    T **board=new T*[size];
    for (int i=0; i<size; i++)
    {
       board[i] = new T[size];
       for (int j=0; j<size; j++)
         board[i][j]=0;
    }
    return board;
}
