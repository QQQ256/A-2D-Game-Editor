#include "Engine.hpp"

#include <map>
#include <string>
#include <memory>
#include <iterator>

const int FPS = 30;
const float Delta = 1000 / FPS;

const int FRAME = 6;

extern ECSCoordinator coordinator;

Engine::Engine()
{
    m_ECSCoordinator    = std::make_unique<ECSCoordinator>();
    m_ECSFactory        = std::make_unique<ECSFactory>();
}

// Proper shutdown and destroy initialized objects
Engine::~Engine(){
}

// set frame rate
void Engine::SetFrameRate(int frame){
    int startTime = SDL_GetTicks();

    int curDelta = SDL_GetTicks() - startTime;

    // 1000 / 60 = 16.67, which means that we should refreash 1 frame per 16.67 ms
    // if curDelta is less than 16.67, it means that the refresh speed is so fast
    // so we should delay the difference to enable next frame 
    if (curDelta < Delta)
    {
        SDL_Delay(Delta - curDelta);
    }
}

// Return Input
void Engine::Input(bool *quit){
    
    // TODO: controller is nullptr
    
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
      //Handle events on queue
      while(SDL_PollEvent( &e ) != 0){
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if(e.type == SDL_QUIT){
          *quit = true;
        }
    }
}

// Update SDL
void Engine::Update()
{
}


// Render
// The render function gets called once per loop
void Engine::Render(){
}

void Engine::MainGameLoop()
{
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;

    // While application is running
    while (!quit)
    {
        // Get user input
        Input(&quit);

        SetFrameRate(60);

        coordinator.m_PlayerControllerSystem->Update();

        coordinator.m_SpriteSystem->Update();

        coordinator.m_RenderSystem->Render();

        coordinator.m_InputSystem->Update();

        coordinator.m_LevelEditorSystem->Update();

        // coordinator.m_
    }
    // Disable text input
    SDL_StopTextInput();
}

void Engine::Start(){
    // Report which subsystems are being initialized
    // if(mRenderer!=nullptr){
    //     std::cout << "Initializing Graphics Subsystem\n";
    // }else{
    //     std::cout << "No Graphics Subsystem initialized\n";
    // }

    // Setup TileMap
    // This tile map is 20x11 in our game
    // It is using a 'reference' tilemap with 8x8 tiles
    // that are each 64x64 pixels.
    // tileMap = new GameObject();
    // auto backgroundTileMap = make_shared<TileMapComponent>("./images/Tiles1.bmp",8,8,64,64,20,11,renderer,*tileMap);
    // tileMap->AddComponent(backgroundTileMap);

    // // call component function
    // backgroundTileMap->GenerateSimpleMap();
    // backgroundTileMap->PrintMap();
}

void Engine::Shutdown(){
    // Shut down our Tile Systems
    // if(nullptr != mRenderer){
    //     delete mRenderer;
    // }
}

void Engine::InitializeGraphicsSubSystem(){
    // Setup our Renderer
    // mRenderer = new SDLGraphicsEngineRenderer(screenWidth, screenHeight);
    // if(nullptr == mRenderer){
    //     exit(1); // Terminate program if renderer 
    //              // cannot be created.
    //              // (Optional) TODO:   Could put an error 
    //              //                    messeage, or try to 
    //              //                    reinitialize the engine 
    //              //                    with a different render
    // }
}

void Engine::Init(){

    m_ECSFactory->Init();

}