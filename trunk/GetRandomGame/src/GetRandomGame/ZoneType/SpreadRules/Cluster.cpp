#include "ZoneType/SpreadRules/Cluster.h"
#include <stdlib.h>

void Cluster::Spread(char** map, std::vector<point*>* possible, int mapsize, char typePlaced, char biomeType, int nb)
{
    bool found=false;
    int num=rand()%((int)(possible->size()));


    int x=possible->at(num)->Getx();
    int y=possible->at(num)->Gety();
    map[x][y]=typePlaced;

    for(int i=0;i<nb-1;i++)
    {
        //determine par ou la ville pousse
        int dirX = 0;
        int dirY = 0;
        while(dirX==0&&dirY==0)
        {

                dirX = (rand()%3)-1;

                dirY = (rand()%3)-1;


        }




        bool found=false;
        int devX=0;
        int devY=0;
        //tant qu'on a pas trouver une case on va avancer dans le même direction
        while(!found)
        {
            devX+=(dirX);
            devY+=(dirY);
            if (devX+x<0||devY+y<0||devX+x>=mapsize||devY+y>=mapsize)
            {
                //on se cancel en atteignant le bord de la map
                found=true;
                return;
            }
            if(map[x+devX][y+devY]==biomeType)
            {
                map[x+devX][y+devY]=typePlaced;
                found=true;
            }
        }

    }


}
