#include "System.hpp"
#include <vector>

using namespace std;

// 现在的m_Entity在RenderSystem中毫无作用，原因是我需要基于entity中的Render组件的值进行排序，但是我真不知道怎么写。。。有空再改
// class EntityRenderPriorityComparator {
// public:
//     set<Entity, EntityRenderPriorityComparator> m_SortedEntities;

//     bool operator()(const Entity& a, const Entity& b) const {
//         auto& rendererA = coordinator.GetComponent<Renderer>(a);
//         auto& rendererB = coordinator.GetComponent<Renderer>(b);
//         return rendererA.renderPriority < rendererB.renderPriority;
//     }
// };

class RenderSystem : public ISystem{
public:
	void Init() override;

	void Update() override;
    
    void Render();

    /// @brief [This function is not elegant!] Order entites based on render priority
    /// @param entity entites that require render
    void AddEntity(Entity entity);

private:

    void SortRenderOrder();
    
    void RenderTilemap(Tilemap& tilemap, SDL_Rect src, SDL_Rect dest);

    void RenderSprite(Sprite& sprite);

    void OnTileMapDataChanged(const Event& event);

    void OnCameraMove(const Event &event);


    void OnLevelDataLoaded(const Event& event);

    void CreateTilemapTexture(Tilemap& tilemap);

    int GetTileType(int x, int y, Tilemap& tilemap);

    SDL_Renderer*   m_Render            = nullptr;

    SDL_Texture*    m_TilemapTexture    = nullptr;

    vector<Entity>  entityList          = {};

    /// @brief Tilemap's data is transfered by event
    Tilemap        m_TileMap;

    /// @brief in editor mode, set the start render pos of the game
    SDL_Rect        m_Camera;
    SDL_Rect        m_Editor_GameDest;
    SDL_Rect        m_Game_GameDest;

    GAME_STATE      m_State;
};