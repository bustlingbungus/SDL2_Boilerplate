#define SDL_MAIN_HANDLED

// sdl
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "sdl/LWindow.hpp"
#include "sdl/LTexture.hpp"
#include "sdl/LAudio.hpp"

// std
#include <iostream>
#include <memory>

int main()
{
    // window dimensions
    int WIDTH = 540, HEIGHT = 540;
    auto window = std::make_shared<LWindow>(WIDTH, HEIGHT, "SDL Boilerplate");

    // basic texture
    auto tex = std::make_shared<LTexture>(window);
    tex->loadFromRenderedText("Welcome to SDL!");

    SDL_Event e;
    bool quit = false;
    // main window loop
    while (!quit)
    {
        // handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) quit = true;
            window->handleEvent(e);
        }

        // render when not minimised
        if (!window->isMinimized())
        {
            // clear the window
            SDL_SetRenderDrawColor(window->gRenderer, 0, 0, 0, 0xFF);
            SDL_RenderClear(window->gRenderer);

            tex->render(10, 10);

            // update the window
            SDL_RenderPresent(window->gRenderer);
        }
    }

    return 0;
}