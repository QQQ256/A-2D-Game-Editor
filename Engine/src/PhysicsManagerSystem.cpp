#include "ECSCoordinator.hpp"


extern ECSCoordinator coordinator;

class MyContactListener : public b2ContactListener {
public:
    virtual void BeginContact(b2Contact* contact) override {
        // This function is called when two fixtures begin to touch
        // b2Body* bodyA = contact->GetFixtureA()->GetBody();
        // b2Body* bodyB = contact->GetFixtureB()->GetBody();
        // Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
        // Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);
        // TODO Add Collision Effect
        // PhysicsBody physicsBodyA = coordinator.GetComponent<PhysicsBody>(*entityA);
        // PhysicsBody physicsBodyB = coordinator.GetComponent<PhysicsBody>(*entityB);
        // physicsBodyA.hasCollided = true;
        // physicsBodyB.hasCollided = true;
        cout << "contact detected!" << endl;
    }
    virtual void EndContact(b2Contact* contact) override {
        // This function is called when two fixtures cease to touch
        // b2Body* bodyA = contact->GetFixtureA()->GetBody();
        // b2Body* bodyB = contact->GetFixtureB()->GetBody();
        // Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
        // Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);
        // TODO Add Collision Effect
        // PhysicsBody physicsBodyA = coordinator.GetComponent<PhysicsBody>(*entityA);
        // PhysicsBody physicsBodyB = coordinator.GetComponent<PhysicsBody>(*entityB);
        // physicsBodyA.hasCollided = false;
        // physicsBodyB.hasCollided = false;
    }
};

void PhysicsManagerSystem::Init(){
    mWorld = new b2World(b2Vec2(0.0f, 0.0f));
    mContactListener = new MyContactListener();
    mWorld->SetContactListener(mContactListener);
    std::cout << "PhysicsManagerSystem initialized!" << std::endl;
}

void PhysicsManagerSystem::Init(float gx, float gy){
    mWorld = new b2World(b2Vec2(gx, gy));
    mContactListener = new MyContactListener();
    mWorld->SetContactListener(mContactListener);
    std::cout << "PhysicsManagerSystem initialized!" << std::endl;
}

b2Body* PhysicsManagerSystem::CreateB2Body(Entity entity, BodyType bodyType) {
    b2Body* mBody;
    if (coordinator.HashComponent<Sprite>(entity)) {
        auto& sprite = coordinator.GetComponent<Sprite>(entity);
        b2BodyDef bodyDef;
        std::cout << "Mario entity size w: " << sprite.m_Dest.w << ", h:" << sprite.m_Dest.h << std::endl;
        bodyDef.type = (bodyType == BodyType::DYNAMIC_SOLID ? b2_dynamicBody : b2_staticBody);
        bodyDef.position.x = (sprite.m_Dest.x + 0.5f * sprite.m_Dest.w) * GAME_TO_PHYSICS_SCALE;
        bodyDef.position.y = (sprite.m_Dest.y + 0.5f * sprite.m_Dest.h) * GAME_TO_PHYSICS_SCALE;
        bodyDef.linearDamping = 0.0f;
        bodyDef.fixedRotation = true;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&entity);
        mBody = mWorld->CreateBody(&bodyDef);

        b2PolygonShape polygonShape;
        polygonShape.SetAsBox(2 * sprite.m_Dest.w * GAME_TO_PHYSICS_SCALE, 2 * sprite.m_Dest.h * GAME_TO_PHYSICS_SCALE);
        b2FixtureDef fixtureDef;
        fixtureDef.shape=&polygonShape;
        fixtureDef.friction=0.0f;
        fixtureDef.isSensor = (bodyType == BodyType::STATIC_SENSOR);
        fixtureDef.density = (bodyType == BodyType::DYNAMIC_SOLID) ? 1.0 : 0.0;
        mBody->CreateFixture(&fixtureDef);
    }
    return mBody;
}

void PhysicsManagerSystem::RemoveB2Body(Entity entity) {
    if (coordinator.HashComponent<PhysicsBody>(entity)) {
        PhysicsBody mPhysicsBody = coordinator.GetComponent<PhysicsBody>(entity);
        mWorld->DestroyBody(mPhysicsBody.mBody);
    }
}

void PhysicsManagerSystem::SetB2BodyVx(Entity entity, float vx) {
    if (coordinator.HashComponent<PhysicsBody>(entity)) {
        PhysicsBody mPhysicsBody = coordinator.GetComponent<PhysicsBody>(entity);
        mPhysicsBody.mBody->SetLinearVelocity(b2Vec2(vx * GAME_TO_PHYSICS_SCALE, mPhysicsBody.mBody->GetLinearVelocity().y));
    }
}

void PhysicsManagerSystem::SetB2BodyVy(Entity entity, float vy) {
    if (coordinator.HashComponent<PhysicsBody>(entity)) {
        PhysicsBody mPhysicsBody = coordinator.GetComponent<PhysicsBody>(entity);
        mPhysicsBody.mBody->SetLinearVelocity(b2Vec2(mPhysicsBody.mBody->GetLinearVelocity().x, vy * GAME_TO_PHYSICS_SCALE));
    }
}

void PhysicsManagerSystem::AddB2BodyF(Entity entity, float fx, float fy) {
    if (coordinator.HashComponent<PhysicsBody>(entity)) {
        PhysicsBody mPhysicsBody = coordinator.GetComponent<PhysicsBody>(entity);
        mPhysicsBody.mBody->ApplyForce(b2Vec2(fx * GAME_TO_PHYSICS_SCALE, fy * GAME_TO_PHYSICS_SCALE), mPhysicsBody.mBody->GetPosition(), true);
    }
}

void PhysicsManagerSystem::Update() {
    const float timeStep = 1.0f / 60.0f;
    const int velocityIterations = 6;
    const int positionIterations = 2;

    mWorld->Step(timeStep, velocityIterations, positionIterations);

    PostStep();

    /*
    b2Contact *contact = mWorld->GetContactList();
    while(contact){
        if(contact->IsTouching()){
            b2Body* bodyA = contact->GetFixtureA()->GetBody();
            b2Body* bodyB = contact->GetFixtureB()->GetBody();
            Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
            Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);
            // TODO Add Collision Effect
            PhysicsBody physicsBodyA = engine.GetComponent<PhysicsBody>(*entityA);
            PhysicsBody physicsBodyB = engine.GetComponent<PhysicsBody>(*entityB);
            physicsBodyA.hasCollided = true;
            physicsBodyB.hasCollided = true;
        }
        contact= contact->GetNext();
    }
    */
}

void PhysicsManagerSystem::PostStep() {
    for(auto& entity : m_Entities) {
        if (coordinator.HashComponent<PhysicsBody>(entity) && coordinator.HashComponent<Sprite>(entity)) {
            auto& sprite = coordinator.GetComponent<Sprite>(entity);
            auto& mPhysicsBody = coordinator.GetComponent<PhysicsBody>(entity);
            b2Vec2 position = mPhysicsBody.mBody->GetPosition();
            // std::cout << "b2Body Position X: " << position.x << ", Position Y: " << position.y << std::endl;
            // std::cout << "b2Body Velocity Y: " << mPhysicsBody.mBody->GetLinearVelocity().y << std::endl;
            sprite.m_Dest.x = position.x / GAME_TO_PHYSICS_SCALE - 0.5f * sprite.m_Dest.w;
            sprite.m_Dest.y = position.y / GAME_TO_PHYSICS_SCALE - 0.5f * sprite.m_Dest.h;
        }
    }
}

void PhysicsManagerSystem::SetGravity(float gx, float gy) {
    if (mWorld != nullptr) {
        mWorld->SetGravity(b2Vec2(gx, gy));
    }
}



void PhysicsManagerSystem::SetCollision(Entity entity, bool collision) {
    PhysicsBody mPhysicsBody = coordinator.GetComponent<PhysicsBody>(entity);
    mPhysicsBody.hasCollided = collision;

}

