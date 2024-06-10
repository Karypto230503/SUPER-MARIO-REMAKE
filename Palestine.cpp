#include "Palestine.h"
#include "Resources.h"

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

Palestine::~Palestine()
{
	Physics::world->DestroyBody(body);
}

void Palestine::Begin()
{
	tag = "palestine";

	animation = Animation(1.4f,
		{
			AnimFrame(0.0f, Resources::textures["palestine.png"]),
		});

	b2BodyDef bodyDef{};
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = Physics::world->CreateBody(&bodyDef);
	b2PolygonShape shape{};
	shape.SetAsBox(0.4f, 0.4f);

	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Object;
	fixtureData->object = this;

	b2FixtureDef fixtureDef{};
	fixtureDef.userData.pointer = (uintptr_t)fixtureData;
	fixtureDef.isSensor = true;
	fixtureDef.density = 0.0f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
}

void Palestine::Update(float deltaTime)
{
	animation.Update(deltaTime);
}

void Palestine::Render(Renderer& renderer)
{
	renderer.Draw(animation.GetTexture(), position, sf::Vector2f(0.8f, 0.8f));
}