#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Create Boundries and such
class Platforms{
private:
    string name;
    Texture text;
    Sprite sprite;


public:
    Platforms(String path, float col, float row);
    Platforms(float col, float row, float col2, float row2);
    Sprite& getSprite();
};
