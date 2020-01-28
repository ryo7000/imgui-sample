#ifndef SRC_MVP_WINDOW_H
#define SRC_MVP_WINDOW_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct view {
  glm::vec3 pos{0.0f, 0.0f, -1.0f};
  glm::vec3 target{0.0f, 0.0f, 1.0f};
  glm::vec3 up{0.0f, 1.0f, 0.0f};
};

struct projection {
  float fov{glm::radians(90.0f)};
  float aspect{1.0f};
  float near{0.1f};
  float far{100.0f};
};

struct mvp {
  glm::mat4 model() const {
    return trans * rotate * scale;
  }

  glm::mat4 create() const {
    auto proj = glm::perspective(p.fov, p.aspect, p.near, p.far);
    auto view = glm::lookAt(v.pos, v.target, v.up);
    return proj * view * model();
  }

  glm::mat4 trans{1.0f};
  glm::mat4 rotate{1.0f};
  glm::mat4 scale{1.0f};
  view v;
  projection p;
};

void create_mvp_window(mvp& mvp);

#endif //SRC_MVP_WINDOW_H
