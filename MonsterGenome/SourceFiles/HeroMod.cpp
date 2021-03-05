#include "../HeaderFiles/HeroMod.h"

HeroMod::HeroMod(std::map<std::string, sf::Keyboard::Key>* controlMapping, float width, float height){
    for(int i = 0; i < sizeof(funct)/sizeof(funct[0]); i++){
        funct[i] = i;
    }
    randomize();

    this->controlMapping = controlMapping;

    font.loadFromFile(pixelFont);
    selected = 0;

    // TODO: Make game logo
    title.setString("Choose Mutation");
    title.setFont(font);
    title.setFillColor(Color::Blue);
    title.setCharacterSize(100);
    FloatRect titleBox = title.getGlobalBounds();
    float titleOffset = titleBox.width / 2;
    title.setPosition((width / 2) - titleOffset, 0);
    title.setStyle(Text::Underlined);

    for(int i = 0; i < 3; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Yellow);
        text[i].setCharacterSize(75);

        FloatRect box = text[i].getGlobalBounds();
        float offset = box.width / 2;
        text[i].setPosition((width / 2) - offset, (height / (3 + 1) * (i + 1)));

    }

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}
// Add new modifications here
void HeroMod::modification(Character* hero, int select){
    switch(select){
        case 0 :
            hero->getSprite().setColor(Color::Red);
            break;
        case 1 :
            hero->getSprite().setColor(Color::Green);
            break;
        case 2 :
            hero->getSprite().setColor(Color::Blue);
            break;
        case 3 :
            hero->getSprite().setColor(Color::Yellow);
            break;
        case 4 :
            hero->getSprite().setColor(Color::Magenta);
            break;
        case 5 :
            hero->getSprite().setColor(Color::Cyan);
            break;
    }
}
//Add String to display for modification choice here
string HeroMod::modificationString(int select){
    switch(select){
        case 0 :
            return "Red";
        case 1 :
            return "Green";
        case 2 :
            return "Blue";
        case 3 :
            return "Yellow";
        case 4 :
            return "Magenta";
        case 5 :
            return "Cyan";
        default:
            return "Wrong";
    }
}

void HeroMod::randomize(){
    random_shuffle(begin(funct), end(funct));
    
    for(int i = 0; i < sizeof(text)/sizeof(text[0]); i++){
        text[i].setString(modificationString(funct[i]));
    }
}

void HeroMod::Draw(RenderWindow &window){
    Texture texture;
    texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
    Sprite background(texture);
    background.setPosition(0, 0);
    window.draw(background);

    window.draw(title);

    for(int i = 0; i < sizeof(text)/sizeof(text[0]); i++){
        window.draw(text[i]);
    }
}

bool HeroMod::PollMenu(RenderWindow &window, GameState &state, bool& modify, Character* hero){
    Event event;    
    while(window.pollEvent(event)) {
        if(event.type == Event::Closed){
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            auto pressed = event.key.code;
            // Needs to dereference controlMapping in order to read map
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;
            if(event.key.code == controls["Pause"]){
                state.Pause();
                state.SetState(GameState::PAUSE);
            }
            if (pressed == controls["Jump"]) {
                MoveUp();
            }
            if (pressed == controls["Crouch"]) {
                MoveDown();
            }
            // TODO: Define general controls for this command
            if (pressed == Keyboard::Return) {
                modification(hero, funct[selected]);
                return true;
            }
        }
    }
    return false;
}

void HeroMod::MoveUp(){
    if(selected - 1 >= 0){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected--;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

void HeroMod::MoveDown(){
    if(selected + 1 < 3){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected++;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}