#include "view_menubar.h"
#include "imgui/imgui.h"

namespace vts 
{

void ShowMenuBar() {
    if(ImGui::BeginMenuBar()) {
        // TODO: implement menu
        if(ImGui::BeginMenu("I am a menu")) {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

}