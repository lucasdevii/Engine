#pragma once

#include <SDL3/SDL.h>

class Window {
    public:
        SDL_Window* window = nullptr;
        bool running = false;

        Window(int height, int width, const char* name);
        int Open();

        ~Window();

};