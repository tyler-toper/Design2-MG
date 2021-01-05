#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace std;
using namespace sf;

void runGame(){
    RenderWindow window(VideoMode(1920, 1080), "The Monster Genome");

    while(window.isOpen()){
        window.clear(Color::White);

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }

        window.display();
    }
}

int main() {
    runGame();
    return 0;
}
