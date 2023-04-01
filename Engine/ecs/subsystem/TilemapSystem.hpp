#include "System.hpp"
#include "Tilemap.hpp"
#include "Event.hpp"

#include <vector>

using namespace std;

class TilemapSystem : public ISystem{
public:
	void Init() override;

	void Update() override;

    Tilemap CreateTileMap(string tileSheetFileName, int rows, int cols, int TileWidth, int TileHeight, int mapX, int mapY, int scaleFactor, vector<int>& m_TileMapVector);

    void Editor_SetTile(int x, int y, int type);

    ~TilemapSystem();

private:

    /// @brief legacy，之前mike写的
    void GenerateSimpleMap();

    void SetTile(int x, int y, int type);

    void PrintMap();

    int GetTileType(int x, int y);

    /// @brief send level data to subscribers
    /// @param levelData 
    void DispatchLevelData(vector<int>& levelData);

    /// @brief Store tilemap object from JSON
    Tilemap                 m_TileMap                       = {};
    vector<vector<int>>     m_TileMapVector                 = {};
    SDL_Renderer*           m_Render                        = nullptr;
    SDL_Texture*            m_TilemapTexture                = nullptr;
};