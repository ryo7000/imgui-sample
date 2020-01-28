#include "mvp_window.h"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "imgui.h"

void create_mvp_window(mvp &mvp) {
  ImGui::Begin("mvp");

  ImGui::Text("model");
  ImGui::Indent();
  {
    ImGui::PushItemWidth(80.0f);
    auto model = mvp.model();
    for (int i = 0; i < 4; i++) {
      ImGui::BeginGroup();
      for (int j = 0; j < 4; j++) {
        ImGui::PushID(i * 4 + j);
        ImGui::DragFloat("##model", &model[i][j], 0.01f, -1.0f, 1.0f);
        ImGui::PopID();
        ImGui::SameLine();
      }
      ImGui::EndGroup();
    }
    ImGui::Unindent();
  }

  ImGui::Text("view");
  ImGui::Indent();
  ImGui::Text("pos");
  ImGui::BeginGroup();
  for (int i = 0; i < 3; i++) {
    ImGui::PushID(i);
    ImGui::DragFloat("##view_pos", &mvp.v.pos[i], 0.01f, -1.0f, 1.0f);
    ImGui::PopID();
    ImGui::SameLine();
  }
  ImGui::EndGroup();

  ImGui::Text("target");
  ImGui::BeginGroup();
  for (int i = 0; i < 3; i++) {
    ImGui::PushID(i);
    ImGui::DragFloat("##view_target", &mvp.v.target[i], 0.01f, -1.0f, 1.0f);
    ImGui::PopID();
    ImGui::SameLine();
  }
  ImGui::EndGroup();

  ImGui::Text("up");
  ImGui::BeginGroup();
  for (int i = 0; i < 3; i++) {
    ImGui::PushID(i);
    ImGui::DragFloat("##view_up", &mvp.v.up[i], 0.01f, -1.0f, 1.0f);
    ImGui::PopID();
    ImGui::SameLine();
  }
  ImGui::EndGroup();
  ImGui::Unindent();

  ImGui::Text("projection");
  ImGui::Indent();
  auto degrees = glm::degrees(mvp.p.fov);
  if (ImGui::DragFloat("fov", &degrees, 0.1f, -180, 180)) {
    mvp.p.fov = glm::radians(degrees);
  }
  ImGui::DragFloat("aspect", &mvp.p.aspect, 0.1f, 0.0f, 1.0f);
  ImGui::DragFloat("near", &mvp.p.near, 0.001f, 0.001f, 0.1f);
  ImGui::DragFloat("far", &mvp.p.far, 1.0f, 1.0f, 200.0f);
  ImGui::Unindent();

  ImGui::End();
}
