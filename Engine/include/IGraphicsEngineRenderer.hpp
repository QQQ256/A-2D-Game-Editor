#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP
// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
//
// Note that your path may be different depending on where you intalled things
//
//
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include "EventManager.hpp"

/**
 * This class serves as an interface to
 * the main graphics renderer for our engine.
 */
class IGraphicsEngineRenderer{
    public:
        /**
         * Constructor
         */
        IGraphicsEngineRenderer(int w, int h) : mScreenWidth(w), mScreenHeight(h) {};
        /**
         * Destructor
         */
        virtual ~IGraphicsEngineRenderer() {};
        /**
         * Set the color for the background whenever
         * the color is cleared.
         */
        virtual void SetRenderDrawColor(int r, int g, int b, int a)=0;
        /**
         * Clear the screen
         */
        virtual void RenderClear()=0;
        /**
         * Render whatever is in the backbuffer to
         * the screen.
         */
        virtual void RenderPresent()=0;

        virtual SDL_Renderer* GetSDLRenderer() = 0;

    protected:
        // Screen dimension constants
        int             mScreenWidth{0};
        int             mScreenHeight{0};
};


class SDLGraphicsEngineRenderer : public IGraphicsEngineRenderer{
    public:
        /** Concrete implementation of constructor
         *
         */
        SDLGraphicsEngineRenderer(int w, int h);
        /** Destructor 
         *
         */
        ~SDLGraphicsEngineRenderer();

        void SetRenderDrawColor(int r, int g, int b, int a) override;
        /**
         * Clear the screen
         */
        void RenderClear() override ;
        /**
         * Render whatever is in the backbuffer to
         * the screen.
         */
        void RenderPresent() override;
        /**
         * Get Pointer to Window
         */
        SDL_Window* GetWindow();
        /**
         * Get Pointer to Renderer
         */
        SDL_Renderer* GetSDLRenderer() override;

        void OnRenderSurfaceCreated(const Event& event);

    private:
        // SDL Window
        SDL_Window*     mWindow = nullptr;
        // SDL Renderer
        SDL_Renderer*   mRenderer = nullptr;
};

#endif
