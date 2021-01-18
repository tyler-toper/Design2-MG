#ifndef MAIN_CPP_MENU_H
#define MAIN_CPP_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define options 3

class Menu{
private:
    int selected;
    Font font;
    Text text[options];

public:
    Menu(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetSelected();

};

#endif //MAIN_CPP_MENU_H
