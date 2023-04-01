#pragma once

#include "System.hpp"
#include "Event.hpp"
#include "Camera.hpp"

class CameraSystem : public ISystem
{
public:
	void Init() override;

	void Update() override;

    void Follow(int x, int y);

    void MoveCamera(int x, int y);

    Camera CreateCamera(float cameraX, float cameraY, float viewportWidth, float viewportHeight,
                      float worldWidth, float worldHeight,
                      float edge = 0.65f);

private:
    void OnKeyboardClicked_A(const Event &event);

    void OnKeyboardClicked_D(const Event &event);

    void OnKeyboardClicked_W(const Event &event);

    void OnKeyboardClicked_S(const Event &event);

    void OnLevelDataLoaded(const Event &event);

    void DispatchCameraMovementPosition(int x, int y);

    float clamp(float v, float lo, float hi)
    {
        return v < lo ? lo : hi < v ? hi
                                    : v;
    }

    Camera      m_Camera;

    Tilemap     m_tilemap; // 这里其实那个reference就好了，懒得改

    SDL_FRect   m_CameraInnerViewport;

    int         m_CameraSpeed;
};