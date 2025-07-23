#include "Engine.h"

#include <SDL3/SDL.h>
#include <iostream>
void HogEngine::Init(const char* title, int w, int h)
{
    std::cout<<windowManager.Init(title, w, h);
    
    bool done = false;
    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // Do game logic, present a frame, etc.
    }


}

void HogEngine::Quit()
{   
    windowManager.Quit();
    // Clean up
    SDL_Quit();
}
