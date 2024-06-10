#include "Game.h"
#include "Resources.h"
#include "Physics.h"
#include "Mario.h"
#include "Map.h"
#include "Palestine.h"
#include <SFML/Audio.hpp>
#include <filesystem>
#include "Highscore.h"


Map map(1.0f);
Camera camera(20.0f);
Mario mario{};
std::vector<Object*> objects{};
sf::Music music{};

bool paused{};
bool gameOver{};
bool victory{};

sf::Image mapImage{};
sf::Font font{};
sf::Text coinsText("Points", font);
sf::Text pausedText("PAUSED", font);
sf::Text gameOverText("GAME OVER", font);
sf::Text victoryText("VICTORY", font);
sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));
Highscore highscore("./resources/highscore.txt");


void Restart()
{
	Physics::Init();

	mario = Mario();
	mario.position = map.CreateFromImage(mapImage, objects);

	mario.isDead = false;
	paused = false;
	gameOver = false;
	victory = false;

	mario.Begin();
	for (auto& object : objects)
	{
		object->Begin();
	}
	music.play();
}

void Begin()
{
	for (auto& file : std::filesystem::directory_iterator("./resources/textures/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
		{
			Resources::textures[file.path().filename().string()].loadFromFile(
				file.path().string());
		}
	}

	for (auto& file : std::filesystem::directory_iterator("./resources/sounds/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".ogg" || file.path().extension() == ".wav"))
		{
			Resources::sounds[file.path().filename().string()].loadFromFile(
				file.path().string());
		}
	}

	music.openFromFile("./resources/sounds/music.ogg");
	music.setLoop(true);
	music.setVolume(25);

	font.loadFromFile("./resources/font.ttf");
	coinsText.setFillColor(sf::Color::White);
	coinsText.setOutlineColor(sf::Color::Black);
	coinsText.setOutlineThickness(1.0f);
	coinsText.setScale(0.1f, 0.1f);

	pausedText.setFillColor(sf::Color::White);
	pausedText.setOutlineColor(sf::Color::Black);
	pausedText.setOutlineThickness(1.0f);
	pausedText.setScale(0.5f, 0.5f);

	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(1.0f);
	gameOverText.setScale(0.5f, 0.5f);

	victoryText.setFillColor(sf::Color::White);
	victoryText.setOutlineColor(sf::Color::Black);
	victoryText.setOutlineThickness(1.0f);
	victoryText.setScale(0.5f, 0.5f);

	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setOrigin(0.5f, 0.5f);

	mapImage.loadFromFile("./resources/mp.png");

	Restart();
}

void Update(float deltaTime)
{
	if ((mario.isDead || victory == true) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Restart();

	if (mario.isDead || paused || gameOver || victory)
		return;

	Physics::Update(deltaTime);
	mario.Update(deltaTime);
	camera.position = mario.position;

	for (auto& object : objects)
	{
		object->Update(deltaTime);
	}
}

void Render(Renderer& renderer)
{
	renderer.Draw(Resources::textures["BG.jpg"], mario.position, camera.GetViewSize());

	map.Draw(renderer);

	for (auto& object : objects)
	{
		object->Render(renderer);
	}

	mario.Draw(renderer);

	Physics::DebugDraw(renderer);
}

void RenderUI(Renderer& renderer)
{
	coinsText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
	coinsText.setString("Score: " + std::to_string(mario.GetCoins()));
	renderer.target.draw(coinsText);

	sf::Vector2f viewCenter = camera.GetUIView().getCenter();
	sf::Vector2f viewSize = camera.GetUIView().getSize();

	if (paused)
	{
		backgroundShape.setScale(viewSize);
		renderer.target.draw(backgroundShape);

		sf::FloatRect textRect = pausedText.getLocalBounds();
		pausedText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
		pausedText.setPosition(viewCenter);
		renderer.target.draw(pausedText);
	}

	if (gameOver)
	{
		backgroundShape.setScale(viewSize);
		renderer.target.draw(backgroundShape);

		sf::FloatRect textRect = gameOverText.getLocalBounds();
		gameOverText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
		gameOverText.setPosition(viewCenter);
		renderer.target.draw(gameOverText);

		int finalScore = mario.GetCoins(); // Updating highscore after game over
		highscore.updateHighscore(finalScore); 
	}

	if (victory)
	{
		backgroundShape.setScale(viewSize);
		renderer.target.draw(backgroundShape);

		sf::FloatRect textRect = victoryText.getLocalBounds();
		victoryText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
		victoryText.setPosition(viewCenter);
		renderer.target.draw(victoryText);

		int finalScore = mario.GetCoins(); 
		highscore.updateHighscore(finalScore); 
	}
}



void DeleteObject(Object* object)
{
	const auto& it = std::find(objects.begin(), objects.end(), object);
	if (it != objects.end())
	{
		delete* it;
		objects.erase(it);
	}
}