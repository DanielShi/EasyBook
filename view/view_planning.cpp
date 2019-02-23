#include <string>
#include <memory>
#include "view_planning.h"
#include "imgui/imgui.h"

namespace vts 
{
void ShowPlanning() {

    ImGui::SetNextWindowContentSize(ImVec2(5500.0f, 0.0f));
    if (ImGui::BeginChild(ImGui::GetID("PlanningChild"), ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar)) {

        int columnCount = 52;
        int columnWidth = 50;
        ImGui::Columns(columnCount, "date", true);
        char label[32];

        ImGuiListClipper clipper(2000);

        while (clipper.Step()) {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
                for (int n = 0; n < columnCount; n++) {
                    ImGui::SetColumnWidth(n, columnWidth);
                    sprintf(label, "column %d", n);
                    if (ImGui::Selectable(label)) {
                    }
                    ImGui::NextColumn();
                }
            }
        }
    }
    ImGui::EndChild();
}
}