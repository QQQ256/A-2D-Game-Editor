#include "ECSCoordinator.hpp"

extern ECSCoordinator coordinator;

void TilemapSystem::Init()
{
    m_Render = coordinator.m_SDLGraphicsSystem->GetSDLRenderer();
    // TODO: 这里没必要创建材质
    m_TilemapTexture = SDL_CreateTexture(
        m_Render,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        WINDOW_WIDTH,
        WINDOW_HIEGHT);
    assert(m_TilemapTexture != nullptr && "TilemapSystem::m_TilemapTexture is null");
    
    
    // coordinator.AddEventListener(EVENT::EVENT_ON_MOUSE_CLICKED, [this](const Event& event){
    //     OnMouseClicked(event);
    // });

    Debug::PrintMessage("Init TilemapSystem");
}

void TilemapSystem::Update()
{
}

TilemapSystem::~TilemapSystem()
{
    if(m_TilemapTexture != nullptr){
        SDL_DestroyTexture(m_TilemapTexture);
        m_TilemapTexture = nullptr;
    }
}

Tilemap TilemapSystem::CreateTileMap(string tileSheetFileName, int _rows, int _cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, int _scaleFactor, vector<int>& m_TileMapVector)
{
    Tilemap _tileMap;
    m_TileMap = _tileMap;
    if (nullptr == m_Render)
    {
        SDL_Log("No valid renderer found");
    }

    // Setup variables
    m_TileMap.m_Rows          = _rows;
    m_TileMap.m_Cols          = _cols;
    m_TileMap.m_TileWidth     = _TileWidth;
    m_TileMap.m_TileHeight    = _TileHeight;
    m_TileMap.m_MapX          = _mapX;
    m_TileMap.m_MapY          = _mapY;
    m_TileMap.m_ScaleFactor   = _scaleFactor;
    m_TileMap.m_Tiles         = m_TileMapVector;

    m_TileMap.m_TileSpriteSheet = ResourceManager::GetInstance().GetSDL_Surface(tileSheetFileName.c_str());

    if (nullptr == m_TileMap.m_TileSpriteSheet)
    {
        SDL_Log("Failed to allocate surface");
    }
    else
    {
        // Create a texture from our surface
        // Textures run faster and take advantage of
        //  hardware acceleration
        // m_TileMap.m_Texture = SDL_CreateTextureFromSurface(ren, m_TileMap.m_TileSpriteSheet);
        m_TileMap.m_Texture = ResourceManager::GetInstance().GetSDL_Texture(tileSheetFileName.c_str(), m_Render, m_TileMap.m_TileSpriteSheet);
    }

    this->DispatchLevelData(m_TileMapVector);
    
    PrintMap();

    return m_TileMap;
}

void TilemapSystem::GenerateSimpleMap()
{
    for (int y = 0; y < m_TileMap.m_MapY; y++)
    {
        for (int x = 0; x < m_TileMap.m_MapX; x++)
        {
            if (y == 0)
            {
                SetTile(x, y, 1);
            }
            if (y == m_TileMap.m_MapY - 1)
            {
                SetTile(x, y, 0);
            }
        }
    }
}

void TilemapSystem::SetTile(int x, int y, int type)
{
    m_TileMap.m_Tiles[y * m_TileMap.m_MapX + x] = type;
}

void TilemapSystem::Editor_SetTile(int mouseX, int mouseY, int type)
{
    int tileX = mouseX / m_TileMap.m_TileWidth;
    int tileY = mouseY / m_TileMap.m_TileHeight;  
}

int TilemapSystem::GetTileType(int x, int y)
{
    return m_TileMap.m_Tiles[y * m_TileMap.m_MapX + x];
}

void TilemapSystem::DispatchLevelData(vector<int> &levelData)
{
    Event event(EVENT::EVENT_ON_LEVEL_DATA_LOADED);
    event.SetParameter<vector<int>>("mapData", levelData);
    event.SetParameter<Tilemap>("mapObject", m_TileMap);

    coordinator.TriggerEvent(event);
}

void TilemapSystem::PrintMap()
{
    Debug::PrintMessage("Printint map: ");
    for (int y = 0; y < m_TileMap.m_MapY; y++)
    {
        for (int x = 0; x < m_TileMap.m_MapX; x++)
        {
            std::cout << " " << GetTileType(x, y);
        }
        std::cout << "\n";
    }
}