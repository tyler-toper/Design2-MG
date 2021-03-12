#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword:public MeleeWeapon {
private:

public:
    Sword(unsigned level, string textureFile);
    virtual ~Sword();

    virtual Sword* clone();
/*    void updateRight(RenderWindow& window, View &playerView);
    void updateLeft(RenderWindow& window, View &playerView);*/
    //void render(RenderWindow& window, View &playerView, bool faceright);
    void render(RenderWindow& window, View &playerView);
    virtual void update(RenderWindow& window, View& playerView);
    virtual void renderRight(RenderWindow& window, View &playerView);
    virtual void renderLeft(RenderWindow& window, View &playerView);
};


#endif //SWORD_H
