#pragma once

#include <box2d/box2d.h>

struct PhysicsBody{
    b2Body* mBody;
    bool hasCollided;
};