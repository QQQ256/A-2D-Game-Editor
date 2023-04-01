#include "ECSCoordinator.hpp"
#include "SpriteSystem.hpp"

extern ECSCoordinator coordinator;

void SpriteSystem::Init(){
    m_Render = coordinator.m_SDLGraphicsSystem->GetSDLRenderer();
    Debug::PrintMessage("Init SpriteRenderSystem");
}


void SpriteSystem::Update(){
    for(auto& entity : m_Entities){
        if(coordinator.HashComponent<Sprite>(entity)){
            auto& sprite = coordinator.GetComponent<Sprite>(entity);
            if(sprite.m_CurrentFrame > sprite.m_Frame){
                sprite.m_CurrentFrame = 0;
            }

            // get the sprite's init size (ex. 16*16)
            sprite.m_Src.x = sprite.m_CurrentFrame * sprite.m_SizeX;
            sprite.m_Src.y = 0;

            // set your destination size in screen
            sprite.m_Dest.w = 64;
            sprite.m_Dest.h = 64;

            sprite.m_CurrentFrame++;
        }
    }
}

Sprite SpriteSystem::CreateSprite(){
    Sprite s;
    return s;
}

Sprite SpriteSystem::CreateSprite(std::string filePath, SDL_Renderer* ren, int sizeX, int sizeY,  int posX, int posY, int frame){
    Sprite s;
    // ResourceManager::GetInstance().LoadResource(filePath.c_str());
    s.m_SpriteSheet = ResourceManager::GetInstance().GetSDL_Surface(filePath.c_str());
    // s.m_SpriteSheet = SDL_LoadBMP(filePath.c_str());
    if(s.m_SpriteSheet == nullptr){
        SDL_Log("Failed to allocate surface");
    }
    else{
        s.m_Texture = ResourceManager::GetInstance().GetSDL_Texture(filePath, ren, s.m_SpriteSheet);
        // s.m_Texture = SDL_CreateTextureFromSurface(ren, s.m_SpriteSheet);
    }
    s.m_Frame = frame;
    s.m_Render = ren;

    s.m_SizeX = sizeX;
    s.m_SizeY = sizeY;

    s.m_Src.x = 0;
    s.m_Src.y = 0;
    s.m_Src.w = sizeX;
    s.m_Src.h = sizeY;
    
    s.m_Dest.x = posX;
    s.m_Dest.y = posY;
    s.m_Dest.w = sizeX;
    s.m_Dest.h = sizeY;
    return s;
}