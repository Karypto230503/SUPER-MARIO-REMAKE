#pragma once
#include "Object.h"
#include "Physics.h"
#include "Animation.h"
#include <box2d/b2_body.h>

class Palestine :
    public Object
{
public:
    ~Palestine();

    virtual void Begin() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer& renderer) override;
private:
    Animation animation;
    b2Body* body;
};