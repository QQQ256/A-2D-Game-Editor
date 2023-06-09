#pragma once
// store all variables/types here
#include <cstdint>
#include <bitset>
#include "json.hpp"

using namespace std;

/// @brief JSON
using json = nlohmann::json;

/// @brief Each Entity has a unique ID
using Entity = size_t;

/// @brief ComponentType is used for set a unique ID for a component
using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;
const int MAX_EntityCount = 100;
using Signature = bitset<MAX_COMPONENTS>;

// Event Type
enum EVENT{
    EVENT_ON_KEYBOARD_CLICKED_A,
    EVENT_ON_KEYBOARD_CLICKED_D,
    EVENT_ON_KEYBOARD_CLICKED_W,
    EVENT_ON_KEYBOARD_CLICKED_S,
    EVENT_ON_KEYBOARD_CLICKED_O,
    EVENT_ON_KEYBOARD_CLICKED_I,
    EVENT_ON_KEYBOARD_CLICKED_U,
    EVENT_ON_MOUSE_CLICKED_LEFT,
    EVENT_ON_MOUSE_CLICKED_RIGHT,
    EVENT_ON_LEVEL_DATA_LOADED,
    EVENT_ON_TILEMAP_CHANGED,
    EVENT_ON_CAMERA_MOVE,
    EVENT_ON_CAMERA_MOVE_LEFT,
    EVENT_ON_CAMERA_MOVE_RIGHT,
    EVENT_ON_PLAYER_MOVE
};
// constexpr

// SDL Render Type
enum SDLType{
    Surface,
    Texture
};

// Window Dimentions
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HIEGHT = 1080;
constexpr int EDITOR_WIDTH = 640;
constexpr int FPS = 60;
constexpr float Delta = 1000 / FPS;
constexpr int FRAME = 60;

// JSON
constexpr const char* COMPONENT_CONFIG = "./config/ComponentConfig.json";
constexpr const char* ENEMY_SPRITE = "./images/sprite.bmp";
constexpr const char* TILEMAP_TXT = "./config/Tilemap_Data.txt";
constexpr const char* UI_CONFIG = "./config/UIConfig.json";
constexpr const char* AUDIO_COIN = "./Resources/Audio/smb_coin.wav";

// Render Order: the bigger number renders first
enum RENDER_ORDER{
    BACKGROUND,
    OBJECT,
    _UI_
};

// Entity Type
enum ENTITY_TYPE{
    ENEMY
};

// Game State
enum GAME_STATE{
    MENU,
    EDITOR,
    GAME
};

// Physics Body Type
enum BodyType {
    DYNAMIC_SOLID,
    STATIC_SOLID,
    STATIC_SENSOR
};