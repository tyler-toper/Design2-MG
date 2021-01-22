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
    Clock clock;
    Time time;
    // Create an example level, We can probably load these from a file later
    vector<Platforms*> borders;
    vector<Projectile*> proj;
    //Invisible Borders
    Platforms* plat = new Platforms(1, 600, 800, 0);
    Platforms* plat1 = new Platforms(1, 600, 0, 0);
    //The ground
    Platforms* plat2 = new Platforms("Images/platform.png", 0, 500);
    //Platforms in air
    Platforms* plat3 = new Platforms("Images/platform2.png", 0, 350);
    Platforms* plat4 = new Platforms("Images/platform2.png", 500, 400);
    Platforms* plat5 = new Platforms("Images/platform2.png", 270, 200);
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
        time = clock.restart();
        hero.updatePostion(borders, proj, time, window);
        
        for(int i=0; i < proj.size(); i++){
            if(!proj[i]->update(borders, time)){
                window.draw(proj[i]->getSprite());
            }
            else{
                delete proj[i]; 
                proj.erase(proj.begin() + i);
            }
        }

        for(int i=0; i < borders.size(); i++){
            window.draw(borders[i]->getSprite());
        }
        window.draw(hero.getSprite());
        
        window.display();
    }
}

int main() {
    runGame();
    return 0;
}