#include "view_easybook.h"
#include "view_menubar.h"
#include "view_planning.h"
#include "imgui/imgui.h"

namespace vts 
{

void ShowEasybookWindow(int width, int height) {

    // Treat the window as root container
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_MenuBar
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse
        | ImGuiWindowFlags_NoMove;

    // The window's position and size should fit the native window
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::GetStyle().WindowRounding = 0.0f;

    if(ImGui::Begin("#EasybookWindow",nullptr,flags)) {

        ShowMenuBar();
        ShowPlanning();

        ImGui::End();
    }
}


}