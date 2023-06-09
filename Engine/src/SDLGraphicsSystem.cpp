#include "ECSCoordinator.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

extern ECSCoordinator coordinator;

void SDLGraphicsSystem::Init(){
    
}

void SDLGraphicsSystem::Update(){

}
void SDLGraphicsSystem::Clear()
{
}

void SDLGraphicsSystem::SetSDLWindow(int w, int h){
    mScreenWidth = w;
    mScreenHeight = h;

    // Initialize random number generation.
   	srand(time(nullptr));

    // Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)< 0){
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    // init SDL2_mixer
    if (Mix_Init(MIX_INIT_OGG) == 0)
    {
        std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Error opening audio: " << Mix_GetError() << std::endl;
        exit(1);
    }

    Mix_Init(0);

    //Create window
    mWindow = SDL_CreateWindow( "Lab", 100, 100, mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN );

    // Check if Window did not create.
    if( nullptr == mWindow){
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    //Create a Renderer to draw on
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Check if Renderer did not create.
    if( nullptr == mRenderer ){
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }
    
    // SDL Setup successfully
    std::cout << "No SDL errors Detected in during init\n\n";
}

SDLGraphicsSystem::~SDLGraphicsSystem(){
    // Destroy Renderer
    SDL_DestroyRenderer(mRenderer);
    //Destroy window
    SDL_DestroyWindow( mWindow );
    // Point mWindow to nullptr to ensure 
	// it points to nothing.
    mRenderer = nullptr;
    mWindow = nullptr;
    
    //Quit SDL subsystems
    SDL_Quit();
}

void SDLGraphicsSystem::SetRenderDrawColor(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(mRenderer, r,g,b,a);
}

void SDLGraphicsSystem::RenderClear(){
    SDL_RenderClear(mRenderer);
}

void SDLGraphicsSystem::RenderPresent(){
    SDL_RenderPresent(mRenderer); 
}

// Get Pointer to Window
SDL_Window* SDLGraphicsSystem::GetWindow(){
    return mWindow;
}

// Get Pointer to Renderer
SDL_Renderer* SDLGraphicsSystem::GetSDLRenderer(){
    if(mRenderer == nullptr){
        cout << "SDL_Renderer* SDLGraphicsSystem::GetSDLRenderer() is null" << endl;
        return nullptr;
    }
    return mRenderer;
}