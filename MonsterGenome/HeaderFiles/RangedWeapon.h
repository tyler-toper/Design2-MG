#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Weapons.h"
using namespace sf;
using namespace std;

class RangedWeapon:public Weapons {
private:

public:

    RangedWeapon(unsigned level, string textureFile);
    virtual ~RangedWeapon();

    virtual RangedWeapon* clone() = 0;

    virtual void update(RenderWindow& window, View& playerView)=0;
    virtual void renderRight(RenderWindow& window, View &playerView)=0;
    virtual void renderLeft(RenderWindow& window, View &playerView)=0;
};


#endif //RANGEDWEAPON_H
