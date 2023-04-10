#pragma once

#include "System.hpp"
#include "Event.hpp"

#include <vector>

using namespace std;

class LevelEditorSystem: public ISystem{
public:
    void Init() override;   
    
    void Update() override;

    void Clear() override;

private:
    
    void OnMouseClicked_Left(const Event& event);

    void OnMouseClicked_Right(const Event& event);

    void OnCameraMove(const Event &event);

    void OnLevelDataLoaded(const Event& event);

    void OnKeybardClicked_O(const Event& event);

    void OnKeybardClicked_I(const Event& event);

    void OnKeybardClicked_U(const Event& event);

    void DispatchTileMapChangedData(const Tilemap& tilemap);

    bool IsMouseWintinGameBoundary(int x, int y);

    bool IsMouseWintinEditorBoundary(int x, int y);

    void SetTile(int x, int y, int type);

    void PutTile(int mouseX, int mouseY, int tileX, int tileY, int cameraOffset, int screenOffset, int tileType);

    /// @brief Expand the map
    /// @param m_LevelData 1d map data
    /// @param size tiles you want to add you the map
    void ConvertRawMapData(vector<int> m_LevelData, int size);

    /// @brief calculate map data based on the 2d array
    // void CalculateRenderedMapData();

    void Print();

    int GetTileType(int x, int y); 

    // save mouse position
    int                 m_MouseX;
    int                 m_MouseY;

    // left side is editor, right side is game
    int                 m_GameAreaWidth;
    // int             m_Max_Tile_Width_Count;
    // int             m_Max_Tile_Height_Count;

    // save level data
    vector<int>         m_LevelData;
    vector<vector<int>> m_TwoDMapData;
    int                 m_TilePixel;
    int                 m_CameraOffset = 0;
    int                 m_CameraSpeed  = 0;
    int                 m_MaxMapWidth;
};