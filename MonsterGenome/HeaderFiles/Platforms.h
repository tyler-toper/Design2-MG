#pragma once
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Create Boundries and such
class Platforms{
protected:
    string name;
private:    
    Texture text;
    Sprite sprite;


public:
    Platforms(String path, float col, float row);
    Platforms(float col, float row, float col2, float row2, bool horiz);
    virtual void update(Time& timein);
    Sprite& getSprite();
    string getName();
};

class MovePlatform : public Platforms{
    private:
    float totaldist = 0.f;
    float speed = 0.f;
    float xspeed;
    float yspeed;
    float fliptime = 0.f;

    public:
    MovePlatform(String path, float col, float row, float endcol, float endrow, float speed);
    void update(Time& timein);
    void reverse();
    float getXspeed();
    float getYspeed();
};