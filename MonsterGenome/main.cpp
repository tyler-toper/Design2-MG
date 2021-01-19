#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Hero.h"

using namespace std;
using namespace sf;

void runGame(){
    RenderWindow window(VideoMode(800, 600), "The Monster Genome");
    Hero hero;
    // Create an example level, We can probably load these from a file later
    vector<Platforms> borders;
    //Invisible Borders
    Platforms plat(1, 600, 800, 0);
    Platforms plat1(1, 600, 0, 0);
    //The ground
    Platforms plat2("Images/platform.png", 0, 500);
    //Platforms in air
    Platforms plat3("Images/platform2.png", 0, 350);
    Platforms plat4("Images/platform2.png", 500, 400);
    Platforms plat5("Images/platform2.png", 270, 200);
    borders.push_back(plat);
    borders.push_back(plat1);
    borders.push_back(plat2);
    borders.push_back(plat3);
    borders.push_back(plat4);
    borders.push_back(plat5);

    while(window.isOpen()){
        window.clear(Color::White);
        
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        hero.updatePostion(borders);

        //Put these in an array and make a function
        window.draw(plat.getSprite());
        window.draw(plat1.getSprite());
        window.draw(plat2.getSprite());
        window.draw(plat3.getSprite());
        window.draw(plat4.getSprite());
        window.draw(plat5.getSprite());
        window.draw(hero.getSprite());

        window.display();
    }
}

int main() {
    runGame();
    return 0;
}
