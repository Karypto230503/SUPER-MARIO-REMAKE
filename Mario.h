#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/b2_body.h>
#include "Animation.h"
#include "Renderer.h"
#include "Physics.h"

class Mario
	: public ContactListener
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) override;

	size_t GetCoins();

	sf::Vector2f position{};
	float angle{};
	bool isDead{};

private:
	Animation runAnimation{};
	sf::Texture textureToDraw{};
	sf::Sound jumpSound{};

	FixtureData fixtureData{};
	b2Body* body{};
	b2Fixture* groundFixture;

	size_t isGrounded{};
	bool facingLeft{};
	size_t coins{};
};