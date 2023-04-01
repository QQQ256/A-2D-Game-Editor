#include "ECSCoordinator.hpp"
#include "LevelEditorSystem.hpp"

extern ECSCoordinator coordinator;

void LevelEditorSystem::Init(){
    // register mouse event
    coordinator.AddEventListener(EVENT::EVENT_ON_MOUSE_CLICKED_LEFT, [this](const Event& event){
        OnMouseClicked_Left(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_MOUSE_CLICKED_RIGHT, [this](const Event& event){
        OnMouseClicked_Right(event);
    });

    // register get level data event
    coordinator.AddEventListener(EVENT::EVENT_ON_LEVEL_DATA_LOADED, [this](const Event& event){
        OnLevelDataLoaded(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_CAMERA_MOVE, [this](const Event& event){
        OnCameraMove(event);
    });

    // [T] 存储地图测试
    coordinator.AddEventListener(EVENT::EVENT_ON_KEYBOARD_CLICKED_O, [this](const Event& event){
        OnKeybardClicked_O(event);
    });
}

void LevelEditorSystem::Update(){
    
}

void LevelEditorSystem::OnMouseClicked_Left(const Event &event)
{
    m_MouseX = event.GetParameter<int>("mouseX");
    m_MouseY = event.GetParameter<int>("mouseY");  

    int tileX = static_cast<int>(std::floor(static_cast<float>(m_MouseX) / m_TilePixel));
    int tileY = m_MouseY / m_TilePixel;
    // 该offset是editor占的多余的像素，需要去掉
    int offset = EDITOR_WIDTH / m_TilePixel;
    
    PutTile(m_MouseX, m_MouseY, tileX, tileY, m_CameraOffset, offset, 2);
}

void LevelEditorSystem::OnMouseClicked_Right(const Event &event)
{
    m_MouseX = event.GetParameter<int>("mouseX");
    m_MouseY = event.GetParameter<int>("mouseY");

    int tileX = static_cast<int>(std::floor(static_cast<float>(m_MouseX) / m_TilePixel));
    int tileY = m_MouseY / m_TilePixel;

    int offset = EDITOR_WIDTH / m_TilePixel;

    PutTile(m_MouseX, m_MouseY, tileX, tileY, m_CameraOffset, offset, -1);
}

void LevelEditorSystem::OnCameraMove(const Event &event)
{
    m_CameraSpeed = event.GetParameter<int>("cameraSpeed");
    m_CameraOffset = event.GetParameter<int>("cameraX");
}

void LevelEditorSystem::OnLevelDataLoaded(const Event &event)
{
    m_LevelData = event.GetParameter<vector<int>>("mapData");
    m_Tilemap   = event.GetParameter<Tilemap>("mapObject");
    m_TilePixel = m_Tilemap.m_TileWidth * m_Tilemap.m_ScaleFactor;
}

void LevelEditorSystem::OnKeybardClicked_O(const Event &event)
{
    cout << "Saving data now!" << endl;
    FileReader::GetInstance().SaveTilemapText(m_Tilemap.m_MapX, m_Tilemap.m_MapY, m_Tilemap.m_Tiles, TILEMAP_TXT);
}

void LevelEditorSystem::DispatchTileMapChangedData(const Tilemap &tilemap)
{
    Event event(EVENT::EVENT_ON_TILEMAP_CHANGED);
    event.SetParameter<Tilemap>("mapData", tilemap);
    cout << "m_TileMap's address in LevelEditorSystem::DispatchTileMapChangedData"<< &tilemap << endl;

    coordinator.TriggerEvent(event);
}

bool LevelEditorSystem::IsMouseWintinGameBoundary(int tileX, int tileY)
{
    // TODO:这里如何确定宽度 (现在的计算方式是以固定屏幕的长宽来算的)
    // 320 / (16 * 4) = 5, so we can put the map on the (5, 0 - maxY) position(minimun position)
    int minX = EDITOR_WIDTH / m_TilePixel;
    int maxX = WINDOW_WIDTH / m_TilePixel;
    int maxY = WINDOW_HIEGHT / m_TilePixel;

    return tileX >= minX && tileX <= maxX && tileY >= 0 && tileY <= maxY;
}

bool LevelEditorSystem::IsMouseWintinEditorBoundary(int tileX, int tileY)
{
    int maxX = EDITOR_WIDTH / m_TilePixel;
    int maxY = WINDOW_HIEGHT / m_TilePixel;

    Debug::PrintMessage("Mouse is under editor boundary");
    cout << tileX << ", " << tileY << endl;

    return tileX >= 0 && tileX < maxX && tileY >= 0 && tileY < maxY;
}

int LevelEditorSystem::GetTileType(int x, int y)
{
    return m_Tilemap.m_Tiles[y * m_Tilemap.m_MapX + x];
}

void LevelEditorSystem::SetTile(int x, int y, int type)
{
    int index = y * m_Tilemap.m_MapX + x;
    if (index > m_LevelData.size())
    {
        cout << "Set tile index out of boundary";
    }
    else
    {
        if(type == GetTileType(x, y)){
            cout << "this tile is the same as you clicked!";
            return;
        }

        cout << "m_LevelData's size is: " << m_LevelData.size() << endl;

        m_Tilemap.m_Tiles[index] = type;

        // send map data to Render system
        DispatchTileMapChangedData(m_Tilemap);
        cout << "Modify tile type: " << index << endl;
        // this->Print();
    }
}

void LevelEditorSystem::PutTile(int mouseX, int mouseY, int tileX, int tileY, int cameraOffset, int screenOffset, int tileType)
{
    if(IsMouseWintinGameBoundary(tileX, tileY)){
        // 有偏移的情况，加上摄像机的偏移
        if(m_CameraOffset != 0 && m_CameraSpeed != 0){
            m_MouseX += m_CameraOffset;
            tileX = static_cast<int>(std::floor(static_cast<float>(m_MouseX) / m_TilePixel));

            // 减掉偏移量，才能找到在地图上的正确值，例如加上偏移是34，但地图最大只有30，此时要减去偏移量
            this->SetTile(tileX - m_CameraOffset / m_TilePixel, tileY, tileType);
        }
        // 没有偏移的情况，正常计算
        else{
            this->SetTile(tileX - screenOffset, tileY, tileType);
        }
        
        Debug::PrintMessage("Mouse is under game boundary");
    }
    else if(IsMouseWintinEditorBoundary(tileX, tileY))
    {
        Debug::PrintMessage("Mouse is under editor boundary");
    }
    else{
        cout << "Editor position out of boundary !!!!" << endl;
    }
}

void LevelEditorSystem::ConvertRawMapData(vector<int> m_LevelData)
{
    // 除以17的原因，是1080/64 = 16.几，这里设成17，通过总数除以17可以算出宽度，也就是在宽度能塞多少个方块
    int height = 17;
    int width = m_LevelData.size() / height;

    vector<vector<int>> tempVector(height, vector<int>(width));

    Debug::PrintMessage("Converting 1d to 2d: ");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempVector[i][j] = m_LevelData[i * width + j];
            cout << tempVector[i][j] << " ";
        }
        cout << endl;
    }

    m_TwoDMapData = tempVector;
}

void LevelEditorSystem::Print()
{
    for (int y = 0; y < m_Tilemap.m_MapY; y++)
    {
        for (int x = 0; x < m_Tilemap.m_MapX; x++)
        {
            std::cout << " " << GetTileType(x, y);
        }
        std::cout << "\n";
    }
}
