#include "ECSCoordinator.hpp"
#include "CameraSystem.hpp"

extern ECSCoordinator coordinator;

void CameraSystem::Init()
{
    m_State = coordinator.m_State;

    coordinator.AddEventListener(EVENT::EVENT_ON_KEYBOARD_CLICKED_A, [this](const Event& event){
        OnKeyboardClicked_A(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_KEYBOARD_CLICKED_D, [this](const Event& event){
        OnKeyboardClicked_D(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_KEYBOARD_CLICKED_W, [this](const Event& event){
        OnKeyboardClicked_W(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_KEYBOARD_CLICKED_S, [this](const Event& event){
        OnKeyboardClicked_S(event);
    });

    // TODO: 这里先在地图加载后去判断当前摄像机的一些数据是否要修改
    coordinator.AddEventListener(EVENT::EVENT_ON_LEVEL_DATA_LOADED, [this](const Event& event){
        OnLevelDataLoaded(event);
    });
}

void CameraSystem::Update()
{

}

void CameraSystem::Follow(int x, int y)
{
}

void CameraSystem::MoveCamera(int x, int y)
{

}

Camera CameraSystem::CreateCamera(float cameraX, float cameraY, float viewportWidth, float viewportHeight, float worldWidth, float worldHeight, float edge)
{
    Camera _camera;
    m_Camera = _camera;
    m_Camera.cameraX = cameraX;
    m_Camera.cameraY = cameraY;
    m_Camera.viewportWidth = viewportWidth;
    m_Camera.viewportHeight = viewportHeight;
    m_Camera.worldWidth = worldWidth;
    m_Camera.worldHeight = worldHeight;
    m_Camera.viewport = {cameraX, cameraY, cameraX + viewportWidth, cameraY + viewportHeight};

    return m_Camera;
}

void CameraSystem::OnKeyboardClicked_A(const Event &event)
{
    // Debug::PrintMessage("A is clicked in CameraSystem");
    if(coordinator.m_State == GAME_STATE::EDITOR){
        m_Camera.cameraX -= m_CameraSpeed;

        // x 所能移动的最大距离
        m_Camera.cameraX = clamp(m_Camera.cameraX, 0, EDITOR_WIDTH);
        // cout << "m_Camera.cameraX is " << m_Camera.cameraX << endl;
        // cout << "m_Camera.worldWidth - m_Camera.viewportWidth " << m_Camera.worldWidth - m_Camera.viewportWidth << endl;

        DispatchCameraMovementPosition(m_Camera.cameraX, m_Camera.cameraY);
    }
}

void CameraSystem::OnKeyboardClicked_D(const Event &event)
{
    // Debug::PrintMessage("D is clicked in CameraSystem");
    if(coordinator.m_State == GAME_STATE::EDITOR){
        m_Camera.cameraX += m_CameraSpeed;

        // x 所能移动的最大距离
        m_Camera.cameraX = clamp(m_Camera.cameraX, 0, EDITOR_WIDTH);
        // cout << "m_Camera.cameraX is " << m_Camera.cameraX << endl;

        DispatchCameraMovementPosition(m_Camera.cameraX, m_Camera.cameraY);
    }
}

void CameraSystem::OnKeyboardClicked_W(const Event &event)
{
    // if(coordinator.m_State == GAME_STATE::EDITOR){
    //     m_Camera.cameraY += m_CameraSpeed;

    //     // y 所能移动的最大距离 
    //     m_Camera.cameraY = clamp(m_Camera.cameraX, 0, 320);
    //     cout << "m_Camera.cameraX is " << m_Camera.cameraX << endl;

    //     DispatchCameraMovementPosition(m_Camera.cameraX, m_Camera.cameraY);
    // }
}

void CameraSystem::OnKeyboardClicked_S(const Event &event)
{

}

void CameraSystem::OnLevelDataLoaded(const Event &event)
{
    m_tilemap = event.GetParameter<Tilemap>("mapObject");
    m_CameraSpeed = m_tilemap.m_TileWidth * m_tilemap.m_ScaleFactor;
    
    // 默认的赋值在entity加入camera后就已经设置对了，这里设置的是editor模式下的一些值
    if (m_State == GAME_STATE::EDITOR)
    {
        m_Camera.cameraX = 0;
        m_Camera.cameraY = 0;
        m_Camera.viewportWidth = 1600;
        m_Camera.viewportHeight = 1080;
        m_Camera.worldWidth = m_tilemap.m_TileWidth * m_tilemap.m_MapX * m_tilemap.m_ScaleFactor; // 这里需要知道tilemap的大小，要基于tilemap的属性去计算游戏地图的最终大小
        m_Camera.worldHeight = m_tilemap.m_TileWidth * m_tilemap.m_MapY * m_tilemap.m_ScaleFactor;
        m_Camera.viewport = {320, 0, 1920, 1080};
        
    }
}

void CameraSystem::DispatchCameraMovementPosition(int x, int y)
{
    Event event(EVENT::EVENT_ON_CAMERA_MOVE);
    event.SetParameter<int>("cameraX", m_Camera.cameraX);
    event.SetParameter<int>("cameraY", m_Camera.cameraY);
    event.SetParameter<int>("cameraSpeed", m_CameraSpeed);

    coordinator.TriggerEvent(event);
}