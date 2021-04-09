#include "../HeaderFiles/GameState.h"
#include "../HeaderFiles/Character.h"

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"

class HeroMod{
    private:
    int selected;
    Font font;
    Text text[6]; //Amount of modifications
    Text title;
    int funct[6]; //Amount of modifications
    std::map<std::string, sf::Keyboard::Key> *controlMapping;

    public:
    HeroMod(std::map<std::string, sf::Keyboard::Key>* controlMapping, float width = 1024, float height = 768);
    void Draw(RenderWindow &window);
    bool PollMenu(RenderWindow &window, GameState &state, bool& modify, Character* hero);
    void MoveUp();
    void MoveDown();
    void modification(Hero* hero, int select);
    string modificationString(int select);
    void randomize();
};