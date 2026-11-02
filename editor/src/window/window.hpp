#pragma once

#include <SDL3/SDL.h>

#pragma once

#include <SDL3/SDL.h>

class Window
{
private:
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    bool running = false;

public:
    int max_fps = 60;
    Window(int height, int width, const char* name);

    int Open();

    ~Window();
};