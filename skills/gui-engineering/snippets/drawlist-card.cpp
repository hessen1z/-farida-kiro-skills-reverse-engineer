#include <imgui.h>

void DrawCard(const ImVec2& pos, const ImVec2& size, const char* title, const char* body)
{
    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImVec2(pos.x, pos.y);
    ImVec2 p1 = ImVec2(pos.x + size.x, pos.y + size.y);

    draw->AddRectFilled(p0, p1, IM_COL32(30, 34, 42, 255), 6.0f);
    draw->AddRect(p0, p1, IM_COL32(70, 76, 90, 255), 6.0f, 0, 1.0f);
    draw->AddText(ImGui::GetFont(), ImGui::GetFont()->FontSize + 2.0f, ImVec2(p0.x + 12.0f, p0.y + 10.0f), IM_COL32(255, 255, 255, 255), title);
    draw->AddText(ImGui::GetFont(), ImGui::GetFont()->FontSize, ImVec2(p0.x + 12.0f, p0.y + 38.0f), IM_COL32(180, 188, 202, 255), body);
}
