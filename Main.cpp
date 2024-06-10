#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Renderer.h"
#include "Menu.h"
#include "Highscore.h"
#include "Mario.h"

int main() {
    Mario mario;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SUPER Mario REMAKE");
    sf::Clock deltaClock;
    Renderer renderer(window);
    window.setFramerateLimit(60);
    sf::Font font;

    if (!font.loadFromFile("./resources/font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    Menu menu(window.getSize().x, window.getSize().y);
    bool gameStarted = false;
    Highscore highscore("./resources/highscore.txt");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                paused = !paused;

            switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Enter:
                    switch (menu.GetPressedItem()) {
                    case 0:
                        std::cout << "Play button has been pressed" << std::endl;
                        gameStarted = true;
                        Begin();
                        break;
                    case 1:
                        std::cout << "Highscore button has been pressed" << std::endl;
                        sf::RenderWindow highscoreWindow(sf::VideoMode(800, 600), "Highscore");
                        while (highscoreWindow.isOpen()) {
                            sf::Event event;
                            while (highscoreWindow.pollEvent(event)) {
                                if (event.type == sf::Event::Closed)
                                    highscoreWindow.close();
                            }
                            highscoreWindow.clear();
                            sf::Text highscoreText;
                            highscoreText.setFont(font);
                            highscoreText.setString("Highscore: " + std::to_string(highscore.getHighscore()));
                            highscoreText.setPosition(200, 150);
                            highscoreWindow.draw(highscoreText);
                            highscoreWindow.display();
                        }
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();

        if (!gameStarted) {
            menu.draw(window);
        }
        else {
            float deltaTime = deltaClock.restart().asSeconds();
            Update(deltaTime);
            window.setView(camera.GetView(window.getSize()));
            Render(renderer);
            window.setView(camera.GetUIView());
            RenderUI(renderer);

        }

        window.display();
    }

    return 0;
}
