#include "./menu.hpp"

#include <cstdarg>
#include <imgui.h>

void Menu::Draw()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui::Begin(
        "Menu",
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );

    ImGui::PushStyleColor(
        ImGuiCol_Text,
        ImVec4(1.0f, 0.2f, 0.2f, 1.0f)
    );
    ImGui::SetWindowFontScale(2.5f);

        ImGui::Text("Meus projetos");

    ImGui::PopStyleColor();


    
    ImGui::End();
}