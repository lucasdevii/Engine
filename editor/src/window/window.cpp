#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "./window.hpp"
#include "../render/panels/menu.hpp"

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

    //Carrega funções do imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplSDL3_InitForOpenGL(
        this->window,
        this->context
    );

    ImGui_ImplOpenGL3_Init("#version 330");
}


int Window::Open()
{
    Menu menu_screen;

    this->running = true;
    SDL_Event event;

    while (this->running)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
            {
                this->running = false;
            }
        }

        // Limpar primeiro
        glClear(GL_COLOR_BUFFER_BIT);

        // Iniciar novo frame do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Construir a interface
        menu_screen.Draw();

        // Renderizar a interface
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(
            ImGui::GetDrawData()
        );

        // Apresentar o frame
        SDL_GL_SwapWindow(this->window);

        SDL_Delay(16);
    }

    return 0;
}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

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