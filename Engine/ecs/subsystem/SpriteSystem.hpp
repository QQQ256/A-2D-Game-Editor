#pragma once

#include "System.hpp"
#include "Sprite.hpp"

using namespace std;

class SpriteSystem : public ISystem{
public:
	void Init() override;

	void Update() override;

    Sprite CreateSprite();

    Sprite CreateSprite(std::string filePath, SDL_Renderer* ren, int sizeX, int sizeY, int posX, int posY, int frame);
private:
    SDL_Renderer*   m_Render      =  nullptr;
};