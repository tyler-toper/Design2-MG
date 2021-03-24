#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapons.h"
using namespace sf;
using namespace std;


class MeleeWeapon:public Weapons{
private:

protected:

public:
    MeleeWeapon(unsigned level, string textureFile);
    virtual ~MeleeWeapon();

    virtual MeleeWeapon* clone() = 0;
    virtual void update(RenderWindow& window, View& playerView)=0;
    virtual void renderRight(RenderWindow& window, View &playerView)=0;
    virtual void renderLeft(RenderWindow& window, View &playerView)=0;

    //virtual void render(RenderTarget& target) = 0;
};


#endif //MELEEWEAPON_H
