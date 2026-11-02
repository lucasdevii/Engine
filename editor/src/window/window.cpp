#include "./window.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdexcept>
#include <string>
#include <exception>
#include <iostream>

Window::Window(int height, int width, const char* name)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION, 3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION, 3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_GL_SetAttribute(
        SDL_GL_DOUBLEBUFFER, 1
    );

    this->window = SDL_CreateWindow(
        name,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    if (!this->window)
    {
        std::string error = SDL_GetError();

        SDL_Quit();

        throw std::runtime_error(error);
    }

    // Criar o contexto OpenGL
    this->context = SDL_GL_CreateContext(
        this->window
    );

    if (!this->context)
    {
        std::string error = SDL_GetError();

        SDL_DestroyWindow(this->window);
        this->window = nullptr;

        SDL_Quit();

        throw std::runtime_error(error);
    }

    // Carregar as funções OpenGL
    if (!gladLoadGL(
        (GLADloadfunc)SDL_GL_GetProcAddress))
    {
        SDL_GL_DestroyContext(this->context);
        this->context = nullptr;

        SDL_DestroyWindow(this->window);
        this->window = nullptr;

        SDL_Quit();

        throw std::runtime_error(
            "Falha ao carregar OpenGL"
        );
    }

    // Configurar a área de renderização
    glViewport(0, 0, width, height);

    // Configurar a cor de fundo
    glClearColor(
        0.1f,
        0.1f,
        0.15f,
        1.0f
    );
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

            // Limpar a tela
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Apresentar o resultado
            SDL_GL_SwapWindow(window);
            
            SDL_Delay(this->max_fps / 1000);
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
    if (this->context != nullptr)
    {
        SDL_GL_DestroyContext(this->context);
        this->context = nullptr;
    }

    if (this->window != nullptr)
    {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }

    SDL_Quit();
}