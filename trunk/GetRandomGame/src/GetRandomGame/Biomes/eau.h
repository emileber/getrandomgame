#ifndef EAU_H
#define EAU_H
#include "Biome.h"


class eau : public Biome
{
    public:
        eau(char t);
        virtual ~eau();
        int generate(char** map, int mapsize);

    protected:
    private:
};

#endif // EAU_H
