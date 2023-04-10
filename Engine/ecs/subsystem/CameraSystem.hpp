#pragma once

#include "System.hpp"
#include "Event.hpp"
#include "Camera.hpp"

class CameraSystem : public ISystem
{
public:
	void Init() override;

	void Update() override;

    void Clear() override;

    void Follow(int x, int y);

    void MoveCamera(int x, int y);

    void EnterState(const GAME_STATE& state);

    Camera CreateCamera(float cameraX, float cameraY, float viewportWidth, float viewportHeight,
                      float worldWidth, float worldHeight,float edge);

private:
    void OnKeyboardClicked_A(const Event &event);

    void OnKeyboardClicked_D(const Event &event);

    void OnKeyboardClicked_W(const Event &event);

    void OnKeyboardClicked_S(const Event &event);

    void OnPlayerMovePosition(const Event &event);

    void OnTilemapChanged(const Event &event);

    void DispatchCameraMovementPosition(int x, int y);

    Camera      m_Camera;

    SDL_Rect    m_CameraInnerViewport;

    int         m_CameraSpeed;
    int         m_MaxMapWidth;

    int         m_PlayerMoveX;
    int         m_PlayerMoveY;

    bool        m_HasPlayerEntity;
};