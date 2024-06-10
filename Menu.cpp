#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("./resources/font.ttf"))
    {
        std::cerr << "Failed to open font file for reading." << std::endl;
    }

    // Load the background texture and set it to a sprite
    if (!backgroundTexture.loadFromFile("./resources/textures/BG1.jpg"))
    {
        std::cerr << "Failed to open menu background file for reading." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u windowSize(width, height);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);

    // Center the sprite in the window
    backgroundSprite.setPosition(windowSize.x / 2, windowSize.y / 2);
    backgroundSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    sf::FloatRect textRect = menu[0].getLocalBounds();
    menu[0].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    menu[0].setPosition(sf::Vector2f(width / 2, height / (2 + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Highscore");
    textRect = menu[1].getLocalBounds();
    menu[1].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    menu[1].setPosition(sf::Vector2f(width / 2, height / (2 + 1) * 2));

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    for (int i = 0; i < 2; i++)
    {
        window.draw(menu[i]);
    }
}


void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < 2)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}