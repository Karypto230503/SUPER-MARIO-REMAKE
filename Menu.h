#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(float width, float height);
   

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[2];
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};
