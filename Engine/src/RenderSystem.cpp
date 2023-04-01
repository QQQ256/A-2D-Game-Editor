#include <algorithm>

#include "ECSCoordinator.hpp"

extern ECSCoordinator coordinator;


void RenderSystem::Init(){
    m_Render = coordinator.m_SDLGraphicsSystem->GetSDLRenderer();
    m_State = coordinator.m_State;
    // int tilePixel = 16;
    // int offsetX   = 5;

    // [editor mode] the start of the game position (render position)
    m_Camera.x = 0;
    m_Camera.y = 0;
    m_Camera.w = (WINDOW_WIDTH - EDITOR_WIDTH);
    m_Camera.h = WINDOW_HIEGHT;

    m_Editor_GameDest.x = EDITOR_WIDTH;
    m_Editor_GameDest.y = 0;
    m_Editor_GameDest.w = WINDOW_WIDTH - EDITOR_WIDTH; // Set width (1920 - 320)
    m_Editor_GameDest.h = WINDOW_HIEGHT; // Set height

    // [game mode] the start of the game position (render position)
    m_Game_GameDest.x = 0;
    m_Game_GameDest.y = 0;
    m_Game_GameDest.w = WINDOW_WIDTH;
    m_Game_GameDest.h = WINDOW_HIEGHT;

    // trigger events with no params
    coordinator.TriggerEvent(EVENT::EVENT_TEST_NO_PARAM);

    coordinator.AddEventListener(EVENT::EVENT_ON_TILEMAP_CHANGED, [this](const Event& event){
        OnTileMapDataChanged(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_CAMERA_MOVE, [this](const Event& event){
        OnCameraMove(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_LEVEL_DATA_LOADED, [this](const Event& event){
        OnLevelDataLoaded(event);
    });
}

void RenderSystem::Render(){
    coordinator.m_SDLGraphicsSystem->SetRenderDrawColor(110, 130,170,0xFF);
    // Clear the screen to the color of the empty framebuffer
    coordinator.m_SDLGraphicsSystem->RenderClear();
    
    // 这里先用entityList了，晚点看有空再用m_Entity去做
    for(auto& entity : entityList){
        if(coordinator.HashComponent<Sprite>(entity)){
            auto& sprite = coordinator.GetComponent<Sprite>(entity);
            RenderSprite(sprite);
        }
        if(coordinator.HashComponent<Tilemap>(entity)){
            if(m_State == GAME_STATE::EDITOR){
                RenderTilemap(m_TileMap, m_Camera, m_Editor_GameDest);
            }
            else if (m_State == GAME_STATE::GAME)
            {
                // RenderTilemap(m_TileMap, m_Game_GameDest);
            }
            
        }
    }

    coordinator.m_SDLGraphicsSystem->RenderPresent();
}

void RenderSystem::Update(){

}

void RenderSystem::RenderTilemap(Tilemap& tilemap, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(m_Render, tilemap.m_FullTexture, &src, &dest);
}

void RenderSystem::RenderSprite(Sprite& sprite){
    SDL_RenderCopy(m_Render, sprite.m_Texture, &sprite.m_Src, &sprite.m_Dest);
}

int RenderSystem::GetTileType(int x, int y, Tilemap& tilemap){
    return tilemap.m_Tiles[y * tilemap.m_MapX + x];
}

void RenderSystem::OnTileMapDataChanged(const Event &event)
{
    m_TileMap = event.GetParameter<Tilemap>("mapData");
    // recreate the tilemap texture to render
    CreateTilemapTexture(m_TileMap);
    cout << "m_TileMap's address in RenderSystem::OnTileMapDataChanged"<< &m_TileMap << endl;
}

void RenderSystem::OnLevelDataLoaded(const Event &event)
{
    m_TileMap = event.GetParameter<Tilemap>("mapObject");
    // 在读取文件后，创建一个巨大的地图texture，之后有修改就修改这个texture
    CreateTilemapTexture(m_TileMap);
}

void RenderSystem::CreateTilemapTexture(Tilemap &tilemap)
{
    /*
        如何将每个单独渲染的tile放到一个大的texture中的方法：

        创建一个大的纹理，其大小等于tilemap的大小。
        设置渲染目标为创建的大纹理。
        遍历tilemap，将每个tile绘制到纹理上。
        将渲染目标重置为默认的渲染目标（窗口）。
    */
    // 1. calculate how big the texture is || 创建一个大的纹理，其大小等于tilemap的大小
    int texture_width = tilemap.m_MapX * tilemap.m_TileWidth * tilemap.m_ScaleFactor;
    int texture_height = tilemap.m_MapY * tilemap.m_TileHeight * tilemap.m_ScaleFactor;
    tilemap.m_FullTexture = SDL_CreateTexture(
        m_Render, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        texture_width, 
        texture_height);
    
    
    // 2. set the target renderer as m_TilemapTexture || 设置渲染目标为创建的大纹理。
    SDL_SetRenderTarget(m_Render, tilemap.m_FullTexture);

    SDL_SetRenderDrawColor(m_Render, 110, 130, 170, 0xFF);
    SDL_RenderClear(m_Render);

    // 3. || 遍历tilemap，将每个tile绘制到纹理上。
    for (int y = 0; y < tilemap.m_MapY; y++)
    {
        for (int x = 0; x < tilemap.m_MapX; x++)
        {
            // Select our Tile
            int currentTile = GetTileType(x, y, tilemap);
            if (currentTile > -1)
            {
                tilemap.m_Src.x = (currentTile % tilemap.m_Cols) * tilemap.m_TileWidth;
                tilemap.m_Src.y = (currentTile / tilemap.m_Rows) * tilemap.m_TileHeight;
                tilemap.m_Src.w = tilemap.m_TileWidth;
                tilemap.m_Src.h = tilemap.m_TileHeight;

                tilemap.m_Dest.x = x * tilemap.m_TileWidth * tilemap.m_ScaleFactor;
                tilemap.m_Dest.y = y * tilemap.m_TileHeight * tilemap.m_ScaleFactor;
                tilemap.m_Dest.w = tilemap.m_TileWidth * tilemap.m_ScaleFactor;
                tilemap.m_Dest.h = tilemap.m_TileHeight * tilemap.m_ScaleFactor;
                // now the m_Render is the tilemap.m_FullTexture
                SDL_RenderCopy(m_Render, tilemap.m_Texture, &tilemap.m_Src, &tilemap.m_Dest);
            }
        }
    }

    // set the render target as default(window)
    // TODO: 修改增删tile的功能
    SDL_SetRenderTarget(m_Render, nullptr);
}

void RenderSystem::AddEntity(Entity entity){
    entityList.push_back(entity);
    SortRenderOrder();
}

// void RenderSystem::UpdateSortedEntities()
// {
//     for (const Entity &entity : m_Entities)
//     {
//         m_SortedEntities.insert(entity);
//     }
// }

void RenderSystem::SortRenderOrder(){
    std::sort(entityList.begin(), entityList.end(), [](const Entity& a, const Entity& b) {
        auto& rendererA = coordinator.GetComponent<Renderer>(a);
        auto& rendererB = coordinator.GetComponent<Renderer>(b);
        return rendererA.renderPriority < rendererB.renderPriority;
    });
}

void RenderSystem::OnCameraMove(const Event &event)
{
    m_Camera.x = event.GetParameter<int>("cameraX");
    m_Camera.y = event.GetParameter<int>("cameraY");
}

// render tilemap legacy
// SDL_Rect Src, Dest;
    // for (int y = 0; y < tilemap.m_MapY; y++)
    // {
    //     // TODO: 这里要加一个摄像机移动的偏移
    //     for (int x = 0; x < tilemap.m_MapX; x++)
    //     {
    //         // Select our Tile
    //         int currentTile = GetTileType(x, y, tilemap);
    //         if (currentTile > -1)
    //         {
    //             // Reverse lookup, given the tile type
    //             // and then figuring out how to select it
    //             // from the texture atlas.
    //             Src.x = (currentTile % tilemap.m_Cols) * tilemap.m_TileWidth;
    //             Src.y = (currentTile / tilemap.m_Rows) * tilemap.m_TileHeight;
    //             Src.w = tilemap.m_TileWidth;
    //             Src.h = tilemap.m_TileHeight;
    //             // Render our Tile at this location
    //             Dest.x = x * tilemap.m_TileWidth * tilemap.m_ScaleFactor;
    //             Dest.y = y * tilemap.m_TileHeight * tilemap.m_ScaleFactor;
    //             Dest.w = tilemap.m_TileHeight * tilemap.m_ScaleFactor;
    //             Dest.h = tilemap.m_TileHeight * tilemap.m_ScaleFactor;
    //             SDL_RenderCopy(m_Render, tilemap.m_Texture, &Src, &Dest);
    //         }
    //     }
    // }