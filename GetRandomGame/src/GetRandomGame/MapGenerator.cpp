#include "MapGenerator.h"
#include <iostream>

using namespace std;
MapGenerator::MapGenerator()
{
    map = new WorldMap(0);
}

WorldMap* MapGenerator::GenerateANewWorld(int size,float smoothing, int rRange)
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
    ds->Randomize(map->getHMap(),smoothing, 65887, rRange, size, 0.0);

std::cout<<"got a hmap"<<std::endl;

    SkewTMap();

    ds->Randomize(map->getTMap(),smoothing, 2323695, rRange, size,0.0);
std::cout<<"got a Tmap"<<std::endl;
    SkewHuMap();

    ds->Randomize(map->getHuMap(),smoothing, 10065, rRange, size,0);
std::cout<<"got a HUmap"<<std::endl;
    SkewVMap();

    ds->Randomize(map->getVMap(),smoothing, 1000000, rRange, size,0);
std::cout<<"got a Vmap"<<std::endl;
    CreateBiomesMap();
    std::cout<<"got a Bmap"<<std::endl;

    return map;
}

void MapGenerator::SkewTMap()
{
    int** tMap = map->getTMap();
    int** hMap = map->getHMap();
    //la map de température est plus froide aux poles et en hauteur
    for(int y =0; y<mapSize; y++)
    {
        //les 3 prochaines lignes batissent un fonction absolu inversé, qui peak au millieu de la map
        int baseT = y-((mapSize-1)/2);

        baseT = ((baseT >= 0) ? -baseT : baseT);

        baseT+=(mapSize-1)/4;



        for(int x=0; x<mapSize; x++)
        {
            tMap[x][y]=baseT-(hMap[x][y]/8);
        }

    }
}

void MapGenerator::SkewHuMap()
{
    int** tMap = map->getTMap();
    int** hMap = map->getHMap();
    int** huMap = map->getHuMap();
    int halfMap=((mapSize-1)/2);

    //les océans augmentent l'humidité autour d'eux, les montagnes augmentent l'humidité vers le millieu et la diminue vers les poles
    //Les températures extremes diminuent l'humidité
    for(int y =0; y<mapSize; y++)
    {

        for(int x=0; x<mapSize; x++)
        {
             int hemisphereMod;
            int absTemp = ((tMap[x][y] >= 0) ? -tMap[x][y] : tMap[x][y]);
            absTemp+=10;
            huMap[x][y]+=absTemp/4;
            if(hMap[x][y]<0)
            {
                for(int i =0; i<3; i++)
                {
                    for(int j =0; j<3;j++)
                    {
                        if((x-1+i)>0&&(x-1+i)<mapSize&&(y-1+i)>0&&(y-1+i)<mapSize)
                            huMap[x-1+i][y-1+j]+=1;
                    }
                }
            }
            else
            {
                if(hMap[x][y]>20)
                {
                    if(y>=halfMap)
                         hemisphereMod = 1;
                    else
                         hemisphereMod = -1;
                    for(int i =0 ;i<4;i++)
                    {
                        if(y-i>0)
                        huMap[x][y-i]+=(i*(hMap[x][y]/4))*hemisphereMod;
                    }
                    for(int i =0 ;i<4;i++)
                    {
                        if(y+i<mapSize)
                        huMap[x][y-i]+=(i*(hMap[x][y]/4))*(-1*hemisphereMod);
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
            vMap[x][y]+=((tMap[x][y]*hMap[x][y])/16)-hMap[x][y]/4;

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
                     biomeMap[x][y]='A';//montagne
                }
                else
                {
                    if(hMap[x][y]>20)
                    {
                        biomeMap[x][y]='M';//grosse montagne
                    }
                    else
                    {
                        if(tMap[x][y]>30)
                        {
                            if(huMap[x][y]>20)
                            {
                                if(vMap[x][y]>20)
                                {
                                    biomeMap[x][y]='W';//Wild Jungle
                                }
                                else
                                {
                                    if(vMap[x][y]>0)
                                    {
                                        biomeMap[x][y]='J';//Jungle
                                    }
                                    else
                                    {
                                        biomeMap[x][y]='R'; // Rainy Grassland
                                    }
                                }
                            }
                            else
                            {
                                if(huMap[x][y]>0)
                                {
                                    if(vMap[x][y]>20)
                                    {
                                        biomeMap[x][y]='w';//Wild Tropical Forest
                                    }
                                    else
                                    {
                                        if(vMap[x][y]>0)
                                        {
                                            biomeMap[x][y]='T';//Tropical Forest
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
                                            biomeMap[x][y]='d';//Desert
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
                                            biomeMap[x][y]='S';//Savannah
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

                                        if(vMap[x][y]>20)
                                        {
                                            biomeMap[x][y]='B';//woodland
                                        }
                                        else
                                        {
                                            if(vMap[x][y]>0)
                                            {
                                                biomeMap[x][y]='b';//boreal grassland
                                            }
                                            else
                                            {
                                                biomeMap[x][y]='H' ;//Thundra
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
                                            if(vMap[x][y]>0)
                                            {
                                                biomeMap[x][y]='I';//Taiga
                                            }
                                            else
                                            {
                                                biomeMap[x][y]='E'; //Eternal Snow
                                            }
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
