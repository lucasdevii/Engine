#include "./menu.hpp"

#include <cstdarg>
#include <imgui.h>

void Menu::Draw()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::Begin(
        "Menu",
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse
    );

    ImGui::Text("Meus projetos");

    if (ImGui::Button("Criar projeto"))
    {
        // Abrir a tela de criação de projeto
    }

    ImGui::End();

}