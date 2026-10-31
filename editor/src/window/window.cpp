#include "./window.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdexcept>
#include <string>
#include <exception>
#include <iostream>

Window::Window(int height, int width, const char* name)
{
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(SDL_GetError());
    }

    this->window = SDL_CreateWindow(
        name,
        width,
        height,
        0
    );

    if (this->window == nullptr) {
        std::string error = SDL_GetError();
        SDL_Quit();
        throw std::runtime_error(error);
    }
}

int Window::Open()
{
    try
    {
        this->running = true;
        SDL_Event event;

        while (this->running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    this->running = false;
                }
            }

            SDL_Delay(16);
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Erro: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

Window::~Window()
{
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}